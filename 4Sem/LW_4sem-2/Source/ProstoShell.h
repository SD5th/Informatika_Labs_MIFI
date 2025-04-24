#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>

#define MAX_LEN 1024
#define MAX_ARGS 64

void shell_loop();

void parse_args(char *line, char **args);

void execute_command(char **args);

void execute_pipeline(char **args1, char **args2);

int is_builtin(char* cmd);

void handle_builtin(char **args);

void bgrep(char *pattern); 

void bgrep(char *pattern) {
  char line[MAX_LEN];
    
  if (pattern == NULL || pattern[0] == '\0') {
    fprintf(stderr, "bgrep: missing pattern\n");
    return;
  }
  
  size_t pattern_len = strlen(pattern);
  
  while (fgets(line, MAX_LEN, stdin)) {
    if (strstr(line, pattern) != NULL) {
      printf("%s", line);
    }
  }
}

int is_builtin(char* cmd) {
  return  strcmp(cmd, "cd") == 0 || 
          strcmp(cmd, "exit") == 0 ||
          strcmp(cmd, "bgrep") == 0;
}

void handle_builtin(char **args) {
  if (strcmp(args[0], "cd") == 0) {
    if (args[1] == NULL) {
      fprintf(stderr, "cd: missing argument\n");
    } 
    else {
      if (chdir(args[1]) != 0) {
        perror("cd");
      }
    }
  } 
  else if (strcmp(args[0], "exit") == 0) {
    exit(0);
  } 
  else if (strcmp(args[0], "bgrep") == 0) {
    if (args[1] == NULL) {
      fprintf(stderr, "bgrep: missing pattern\n");
    } 
    else {
      bgrep(args[1]);
    }
  }
}

void parse_args(char *line, char **args) {
  int i = 0;
  char* token = strtok(line, " \t\n");
  
  while (token != NULL && i < MAX_ARGS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \t\n");
  }
  args[i] = NULL;
}

void execute_command(char **args) {
  if (args[0] == NULL) {
    return;
  }
  
  if (is_builtin(args[0])) {
    handle_builtin(args);
    return;
  }
  
  pid_t pid = fork();
  
  if (pid == 0) {
    execvp(args[0], args);
    perror("execvp");
    exit(1);
  } else if (pid < 0) {
    perror("fork");
  } else {
    wait(NULL);
  }
}

void execute_pipeline(char **args1, char **args2) {
  int pipefd[2];
  pid_t pid1, pid2;
  
  if (pipe(pipefd)) {
    perror("pipe");
    return;
  }
  
  pid1 = fork();
  if (pid1 == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
 
    if (is_builtin(args1[0]))
    {
      handle_builtin(args1);
      exit(EXIT_SUCCESS);
    }
    else
    {
      execvp(args1[0], args1);
      perror("execvp");
      exit(EXIT_FAILURE);
    }
  }
  
  pid2 = fork();
  if (pid2 == 0) {
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    
    if (is_builtin(args2[0]))
    {
      handle_builtin(args2);
      exit(EXIT_SUCCESS);
    }
    else
    {
      execvp(args2[0], args2);
      perror("execvp");
      exit(EXIT_FAILURE);  
    }
  }
  
  close(pipefd[0]);
  close(pipefd[1]);
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
}

void shell_loop() {
  char line[MAX_LEN];
  char *args1[MAX_ARGS];
  char *args2[MAX_ARGS];
  
  while (1) {
    printf("prostoshell> ");
    fflush(stdout);
    
    if (fgets(line, MAX_LEN, stdin) == NULL) {
      printf("\n");
      break;
    }
    
    char* pipe_pos = strchr(line, '|');
    if (pipe_pos != NULL) {
      *pipe_pos = '\0';
      char* cmd1 = line;
      char* cmd2 = pipe_pos + 1;
      
      parse_args(cmd1, args1);
      parse_args(cmd2, args2);
      
      if (args1[0] != NULL && args2[0] != NULL) {
        execute_pipeline(args1, args2);
      }
    } else {
      parse_args(line, args1);
      execute_command(args1);
    }
  }
}