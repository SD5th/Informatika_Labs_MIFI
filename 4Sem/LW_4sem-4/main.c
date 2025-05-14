#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>


#define PORT 80
#define BUFFER_SIZE 1024
#define PATH_SIZE 4096

char SERVER_DIR[PATH_SIZE] = {0};
int SERVER_FD;

volatile sig_atomic_t KEEP_RUNNING = 1;

void handle_signal(int sig) {
  printf("\nhandle_signal called\n");
  KEEP_RUNNING = 0;
}

void init_server(int argc, char* argv[]) {
  printf("Server initializtion started\n");
  
  if (argc < 2) {
    fprintf(stderr, "Error: %s\n", "No port is specified.");
    exit(EXIT_FAILURE);
  }
  
  if (argv[1] == NULL || argv[1][0] == '\0') {
    fprintf(stderr, "Error: %s\n", "Port is empty.");
    exit(EXIT_FAILURE);
  }
  
  if (argv[1][0] == '-' || argv[1][0] == '0') {
    fprintf(stderr, "Error: %s\n", "Port must be a number from 1 to 65535.");
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; argv[1][i] != '\0'; i++)
  {
    if (i == 5)
    {
      fprintf(stderr, "Error: %s\n", "Port must be a number from 1 to 65535.");
      exit(EXIT_FAILURE);
    }
    
    if (!isdigit((unsigned char)argv[1][i]))
    {
      fprintf(stderr, "Error: %s\n", "Port must be a number from 1 to 65535.");
      exit(EXIT_FAILURE);
    }
  }
  
  int port = atoi(argv[1]);
  
  if (!(1 <= port && port <= 65535)) {
    fprintf(stderr, "Error: %s\n", "Port must be a number from 1 to 65535.");
    exit(EXIT_FAILURE);
  }
  SERVER_FD = socket(AF_INET, SOCK_STREAM, 0);
  if (SERVER_FD < 0) { 
    perror("socket"), exit(1);
  }
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  
  if (bind(SERVER_FD, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind"); 
    exit(1);
  }
  
  if (listen(SERVER_FD, 1) < 0) {
    perror("listen"); 
    exit(1);
  }

  printf("Server initializtion ended.\n");
  printf("Server is working on port %d.\n", port);
}

void init_server_dir() {
  printf("Server directory initializtion started\n");
  ssize_t len = readlink("/proc/self/exe", SERVER_DIR, sizeof(SERVER_DIR) - 1);
  if (len == -1) {
    perror("readlink failed");
    exit(EXIT_FAILURE);
  }
  SERVER_DIR[len] = '\0';

  char *last_slash = strrchr(SERVER_DIR, '/');
  if (last_slash == NULL) {
    fprintf(stderr, "Error: Couldn't find a path separator.\n");
    exit(EXIT_FAILURE);
  }
  *(last_slash + 1) = '\0';
  printf("Server directory initializtion ended.\n");
  printf("Server directory is: %s\n", SERVER_DIR);
}

void send_response(int client_fd, const char *status, const char *content_type, const char *body) {
  char response[BUFFER_SIZE];
  int len = snprintf(response, sizeof(response),
    "HTTP/1.1 %s\r\n"
    "Content-Type: %s\r\n"
    "Content-Length: %zu\r\n"
    "Connection: close\r\n"
    "\r\n",
    status, content_type, strlen(body));
  
  if (len < 0 || (size_t)len >= sizeof(response)) {
    const char *err = "HTTP/1.1 500 Internal Server Error\r\n\r\n";
    send(client_fd, err, strlen(err), 0);
    return;
  }
  
  if (send(client_fd, response, len, 0) < 0 || 
    send(client_fd, body, strlen(body), 0) < 0) {
    perror("send failed");
  }
}

void send_file(int client_fd, const char * requested_path) {
  printf("Started send_file\n");
  
  printf("requested_path: %s\n", requested_path);
  char *resolved_path = realpath(requested_path, NULL); 
  printf("resolved_path: %s\n", resolved_path);
  
  if (!resolved_path) {
    send_response(client_fd, "404 Not Found", "text/plain", "404 Not Found\n");
    return;
  }
  


  if (strncmp(resolved_path, SERVER_DIR, strlen(SERVER_DIR)) != 0) {
    send_response(client_fd, "404 Not Found", "text/plain", "404 Not Found\n");
    free(resolved_path);
    return;
  }

  FILE* file = fopen(resolved_path, "rb");
  free(resolved_path);

  if (!file) {
    send_response(client_fd, "404 Not Found", "text/plain", "404 Not Found\n");
    return;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  if (file_size == -1) {
    fclose(file);
    send_response(client_fd, "500 Internal Server Error", "text/plain", "File size error");
    return;
  }

  fseek(file, 0, SEEK_SET);

  char* file_content = malloc(file_size);
  if (!file_content) {
    fclose(file);
    send_response(client_fd, "500 Internal Server Error", "text/plain", "Memory allocation failed");
    return;
  }
  
  size_t read_bytes = fread(file_content, 1, file_size, file);
  if (read_bytes != (size_t)file_size) {
    free(file_content);
    fclose(file);
    send_response(client_fd, "500 Internal Server Error", "text/plain", "File read error");
    return;
  }
  fclose(file);

  char response[BUFFER_SIZE];
  int written = snprintf(response, sizeof(response),
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/octet-stream\r\n"
    "Content-Length: %ld\r\n"
    "Connection: close\r\n"
    "\r\n",
    file_size
  );
  
  if (written < 0 || (size_t)written >= sizeof(response)) {
    free(file_content);
    send_response(client_fd, "500 Internal Server Error", "text/plain", "Response generation failed");
    return;
  }
  
  if (send(client_fd, response, strlen(response), 0) < 0) {
    free(file_content);
    return;  
  }
  send(client_fd, file_content, file_size, 0);

  free(file_content);
}

int main(int argc, char* argv[]) {
  struct sigaction sa;
  sa.sa_handler = handle_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);


  init_server(argc, argv);
  init_server_dir();
  
  char buffer[BUFFER_SIZE];

  while (KEEP_RUNNING == 1) {  
    int client_fd = accept(SERVER_FD, NULL, NULL);
    if (client_fd < 0) {
      if (KEEP_RUNNING != 1) {
        break;
      }
      perror("accept");
      continue;
    }

    ssize_t n = recv(client_fd, buffer, sizeof(buffer)-1, 0);
    if (n > 0) {
      buffer[n] = '\0';
      printf("\n\nReceived:\n%s\n", buffer);
      if (strncmp(buffer, "GET /", 5) == 0) {
        char *path_start = buffer + 5;
        char *path_end = strchr(path_start, ' ');
        if (path_end && path_start != path_end) {
          *path_end = '\0'; 
          char requested_path[PATH_SIZE];
          strcpy(requested_path, SERVER_DIR);
          strcat(requested_path, path_start);
          printf("Requested file: '%s'\n", path_start);
          printf("Requested path: '%s'\n", requested_path);
          send_file(client_fd, requested_path);
        }
        else {
          send_response(client_fd, "404 Not Found", "text/plain", "404 Not Found\n");
        }
      } 
      else {
        send_response(client_fd, "400 Bad Request", "text/plain", "Only GET method is supported\n");
      }
    }
    close(client_fd);
  }
  close(SERVER_FD);
  return 0;
}