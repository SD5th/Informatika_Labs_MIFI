#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 82
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
  char *resolved_path = realpath(requested_path, NULL);  // Нормализация пути

  // Проверка, что файл находится внутри рабочей директории
  if (!resolved_path || strstr(resolved_path, "/home/user/server/") != resolved_path) {
      send_response(client_fd, "403 Forbidden", "text/plain", "Access denied\n");
      free(resolved_path);
      return;
  }
  if (filename)
  FILE* file = fopen(filename, "rb");
  if (!file) {
    send_response(client_fd, "404 Not Found", "text/plain", "404 Not Found");
    return;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* file_content = malloc(file_size + 1);
  fread(file_content, 1, file_size, file);
  fclose(file);

  // Отправляем HTTP-ответ с файлом
  char response[BUFFER_SIZE];
  snprintf(response, sizeof(response),
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: application/octet-stream\r\n"
      "Content-Length: %ld\r\n"
      "Connection: close\r\n"
      "\r\n",
      file_size
  );
  send(client_fd, response, strlen(response), 0);
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
          send_response(client_fd, "404 Not Found", "text/plain", "404 Not Found");
        }
      } 
      else {
        send_response(client_fd, "400 Bad Request", "text/plain", "Only GET method is supported\n");
      }
      //send_response(client_fd, "200 OK", "text/plain", "Hello from server!");
    }

    close(client_fd);
  }
  close(server_fd);
  return 0;
}