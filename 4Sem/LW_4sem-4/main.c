#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 80
#define BUFFER_SIZE 1024

void send_response(int client_fd, const char *status, const char *content_type, const char *body) {
  char response[BUFFER_SIZE];
  snprintf(response, sizeof(response),
      "HTTP/1.1 %s\r\n"
      "Content-Type: %s\r\n"
      "Content-Length: %zu\r\n"
      "Connection: close\r\n"
      "\r\n"
      "%s\r\n",
      status, content_type, strlen(body), body
  );
  send(client_fd, response, strlen(response), 0);
}

void send_file(int client_fd, const char* requested_path) {
  printf("Started send_file\n");
  printf("requested_path: %s\n", requested_path);
  char *resolved_path = realpath(requested_path, NULL); 
  printf("resolved_path: %s\n", resolved_path);
  
  if (!resolved_path) {
    send_response(client_fd, "404 Not Found", "text/plain", "404 Not Found\n");
    return;
  }

  const char* base_dir = "/home/whistling_daddy47/MyFolder/shkool_Labs/4Sem/LW_4sem-4/";
  if (strncmp(resolved_path, base_dir, strlen(base_dir)) != 0) {
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

  // Отправляем HTTP-ответ с файлом
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
    return;  // Ошибка отправки
  }
  send(client_fd, file_content, file_size, 0);
    
  free(file_content);
}

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) { 
    perror("socket"), exit(1);
  }
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT);
  
  if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind"), exit(1);
  }

  if (listen(server_fd, 1) < 0) {
    perror("listen"), exit(1);
  }
  
  char buffer[BUFFER_SIZE];

  while (1 == 1) {  
    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
      perror("accept");
      continue;
    }

    ssize_t n = recv(client_fd, buffer, sizeof(buffer)-1, 0);
    if (n > 0) {
      buffer[n] = '\0';
      printf("\n\nReceived:\n%s", buffer);
      if (strncmp(buffer, "GET /", 5) == 0) {
        char *path_start = buffer + 5;
        char *path_end = strchr(path_start, ' ');
        if (path_end && path_start != path_end) {
          *path_end = '\0'; 
          printf("Requested file: '%s'\n", path_start);
          send_file(client_fd, path_start);
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
  close(server_fd);
  return 0;
}