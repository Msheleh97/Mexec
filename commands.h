/**
 * @brief
 * This modul is responsable of handeling the input file and commands and of the
 * pipes.
 *
 *  @ auother:  Mohammad Mshaleh
 *  @ sine: 02-10-2020
 **/
#ifndef COMMANDS_H
#define COMMANDS_H

/**
* @brief          This function allocate and open pipes. The quantity of pipes
*                 depens on the quantity of command lines.
* @param 1        The quantity of command lines.
* @return         A double pointer into the pipes.
*/int**allocate_pipes(int lines_quantity);

/**
* @brief          This function deallocate the pipes and the list that have all
*                 commands.
* @param 1        A double pointer to the list
* @param 2        A double pointer to the pipes.
* @param 3        A the quantity of command lines.

* @return         noting.
*/void delete_list_and_pipes(char ** list, int **pipes , int size);

/**
* @brief          This function read the command line and sparete in into arguments
* @param 1        A pinter to the command line.
* @return         A double pointer into a list of the arguments.
*/char**get_command_arguments(char *list_of_kommands);

/**
* @brief          This function read and store the input lines in a list line by line .
* @param 1        A pointer to an int to save the quantity of commands lines in.
* @return         A double pointer to a list of commands.
*/char**store_input_commands(int *quantity_of_commands_lines);

/**
* @brief          This function close all open pipes

* @param 1        A double pointer to the pipes.
* @param 2        An int of the quantity of commands lines
* @return         Nothing.
*/void close_pipes(int ** pipes, int quantity_of_commands_lines);

#endif
