/**
 *
 * @brief
 *  This program called mexec. This program is responsable of executing given command.
 *  Mexec uses multiple process to execut the commands. Every command line start a
 *  new process and write the output of the excuted command in a pipe. Exery Process
 *  read the information given by the previous process through the pipe and handle
 *  the given data and writing the output in the pipe infor the next process.
 *  The last process write the output in stdout to show it on the screen.
 *
 *  @ auother:  Mohammad Mshaleh
 *  @ sine: 02-10-2020
 **/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "commands.h"
#include "child.h"

void controll_fork(int fork);
void check_input(int argc,char const *argv[]);

int main(int argc, char const *argv[]){

  char**command_arguments;
  int fork1, lines_quantity = 0;

  check_input(argc,argv);
  char** list_of_commands = store_input_commands(&lines_quantity);

  //If there is one line command.
  if (lines_quantity == 1){
    if(one_line_child(list_of_commands) == 1){
      return EXIT_FAILURE;
    }
    wait(NULL);
    return 0;
  }

  int **pipes = allocate_pipes(lines_quantity);

  //Processing the commands.
  fork1 = fork();
  controll_fork(fork1);
  if (fork1 == 0) {
    command_arguments = get_command_arguments(list_of_commands[0]);
    if(first_child(pipes[0],pipes,lines_quantity,command_arguments) == 1){
      free(command_arguments);
      delete_list_and_pipes(list_of_commands,pipes,lines_quantity);
      exit(1);
    }
    free(command_arguments);
    exit(0);
  }
  for (int i = 1; i < lines_quantity-1 ; i++) {
    fork1 = fork();
    controll_fork(fork1);
    if (fork1 == 0) {
      command_arguments = get_command_arguments(list_of_commands[i]);
      if(between_child(pipes[i-1],pipes[i],pipes,lines_quantity,command_arguments) == 1){
        free(command_arguments);
        delete_list_and_pipes(list_of_commands,pipes,lines_quantity);
        exit(1);
      }
      free(command_arguments);
      exit(0);
    }
  }
  fork1 = fork();
  controll_fork(fork1);
  if (fork1 == 0) {
      command_arguments = get_command_arguments(list_of_commands[lines_quantity-1]);
      if(last_child(pipes[lines_quantity-2],pipes,lines_quantity,command_arguments)== 1){
        free(command_arguments);
        delete_list_and_pipes(list_of_commands,pipes,lines_quantity);
        exit(1);
      }
      free(command_arguments);
      exit(0);
  }

  delete_list_and_pipes(list_of_commands,pipes,lines_quantity);
  int status;
  for (int i = 0; i < lines_quantity; i++){
    if (wait(&status) == -1){
      perror("Error when waiting");
    }
    else if(status != 0){
      return 1;
    }
  }
  return 0;
}



/**
* @brief          This function check if the given arguments quantity is right if
*                 not a eror massage prints.
* @param 1        The quantity of the arguments.
* @param 2        The arguments.
*
* @return         noting.
*/
void check_input (int argc, char const *argv[]){
  if (argc == 2){
    FILE *input = fopen(argv[1],"r");
    if(input == NULL){
      perror(argv[1]);
      exit(1);
    }
    dup2(fileno(input),0);
    close(fileno(input));
    fclose(input);
  }
  if (argc != 1 && argc != 2){
    fprintf(stderr," %d is wrong number of arguments try again\n", argc);
    exit(1);
  }
}

/**
* @brief          This function check if the fork function work correctly. If
*                 Not an error massege prints.
* @param 1        An int given back by the fork.
*
* @return         noting.
*/
void controll_fork(int fork){
  if (fork < 0) {
    perror("Fork\n");
    exit(1);
  }
}
