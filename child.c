#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "commands.h"
#include "child.h"


int first_child(int ch1_to_ch2[],int **pipes, int lines, char **command_arguments){
  if (dup2(ch1_to_ch2[WRITE_END],1) < 0) {
    perror("dup");
    exit(1);
  }
  close_pipes(pipes,lines);
  execvp(command_arguments[0],command_arguments);
  perror("EXEC");
  return 1;
}

int between_child(int ch1_to_ch2[], int ch2_to_ch3[],
                   int **pipes,int lines,char **command_arguments){
  if (dup2(ch2_to_ch3[WRITE_END],1) < 0) {
    perror("dup");
    exit(1);
  }
  if (dup2(ch1_to_ch2[READ_END],0) < 0) {
    perror("dup");
    exit(1);
  }
  close_pipes(pipes,lines);
  execvp(command_arguments[0],command_arguments);
  perror("EXEC");
  return 1;
}

int last_child(int ch2_to_ch3[],int **pipes,int lines,char **command_arguments){
  if (dup2(ch2_to_ch3[READ_END],0) < 0) {
    perror("dup");
    exit(1);
  }
  close_pipes(pipes,lines);
  execvp(command_arguments[0],command_arguments);
  perror("EXEC");
  return 1;
}

int one_line_child (char **list_of_commands){
  int fork1;
  char**command_arguments;
  fork1 = fork();
  if (fork1 < 0) {
    perror("Fork 1 \n");
    exit(1);
  }else if (fork1 == 0) {
    command_arguments = get_command_arguments(list_of_commands[0]);
    execvp(command_arguments[0],command_arguments);
    perror("EXEC");
    return 1;
  }
  free(list_of_commands[0]);
  free(list_of_commands[1]);
  free(list_of_commands);
  return 0;
}
