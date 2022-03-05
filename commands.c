#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "commands.h"

char **store_input_commands(int* quantity_of_commands_lines){
  int temp;
  char **kommando_list = malloc(10 * sizeof(char*));
  if (kommando_list == NULL) {
    fprintf(stderr, "Can't creat a commands list\n");
  }
  do {
    kommando_list[*quantity_of_commands_lines] =(char*)malloc(1024*sizeof(char));
    if (kommando_list[*quantity_of_commands_lines] == NULL) {
      fprintf(stderr, "Can't store a command line\n");
    }
    temp = scanf("%[^\n]%*c",kommando_list[*quantity_of_commands_lines]);
    if (temp == 0) {
      fprintf(stderr, "One of the commands lines is bigger than 1024 character\n");
      exit(1);
    }
    *quantity_of_commands_lines+=1;
    if (*quantity_of_commands_lines >= 10){
      kommando_list = realloc(kommando_list,(*quantity_of_commands_lines*3)*sizeof(char*));
      if (kommando_list == NULL) {
        fprintf(stderr, "Can't realloc\n");
      }
    }
  } while(!feof(stdin));
  *quantity_of_commands_lines-=1;
  return kommando_list;
}


int **allocate_pipes(int lines_quantity){
  int **pipes =  malloc((lines_quantity-1)*sizeof(int*));
  for (int i = 0; i < lines_quantity-1; i++) {
    pipes[i] = malloc(2*sizeof(int));
    if (pipes[i] == NULL){
      fprintf(stderr, "Can't allocate a pipe\n");
    }
  }
  for (int i = 0; i < lines_quantity-1 ; i++) {
    if(pipe(pipes[i]) == -1){
      fprintf(stderr, "Error: can't open a pipe\n");
    }
  }
  return pipes;
}

void delete_list_and_pipes(char ** list, int **pipes, int size){
  close_pipes(pipes,size);
  for (int i = 0; i < size-1; i++) {
    free(pipes[i]);
  }
  free(pipes);
  for (int i = 0; i < size+1 ; i++) {
    free(list[i]);
  }
  free(list);
}


void close_pipes(int ** pipes, int quantity_of_commands_lines){
  int *close_pipes;
  for (int i = 0; i < quantity_of_commands_lines-1; i++) {
    close_pipes = pipes[i];
    close(close_pipes[0]);
    close(close_pipes[1]);
  }
}

char** get_command_arguments(char *list_of_commands){
  int quantity_of_arguments = 2, char_amount = 0, temp = 0;
  int *quantity_of_arguments_characters;
  int size = strlen(list_of_commands);
  for (int i = 0; i < size; i++) {
    if (list_of_commands[i] == 32){
      quantity_of_arguments++;
    }
  }
  quantity_of_arguments_characters = malloc(quantity_of_arguments*sizeof(int));
  if (  quantity_of_arguments_characters == NULL) {
    fprintf(stderr, "Can't allocate  memory for arguments\n");
  }
  for (int i = 0; i < size; i++) {
    if (list_of_commands[i] == 32) {
      quantity_of_arguments_characters[temp] = char_amount+1;
      temp++;
      char_amount = 0;
    }
    char_amount++;
  }
  quantity_of_arguments_characters[temp] = char_amount+1;
  char **command = malloc(quantity_of_arguments*sizeof(char*));
  if (quantity_of_arguments_characters == NULL) {
    fprintf(stderr, "Can't allocate  memory for arguments\n");
  }
  command[0] = strtok(list_of_commands, " ");
  for (int i = 1; i < quantity_of_arguments; i++){
    command[i] = strtok(NULL, " ");
  }
  command[quantity_of_arguments-1] = '\0';
  return command;
}
