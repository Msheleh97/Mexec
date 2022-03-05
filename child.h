/**
 *
 * @brief
 * This modul is responsable of the childern process. It have 4 function there every
 * function is responsable for a diffrent typ of child.
 *
 *  @ auother:  Mohammad Mshaleh
 *  @ sine: 02-10-2020
 **/
#ifndef CHILD_H
#define CHILD_H


#define READ_END 0
#define WRITE_END  1

/**
* @brief          This function is responsable of the first child. It execut the
*                 first command and write the result in the given pipe.
* @param 1        The pipe to write the result in for the next child.
* @param 2        A pointer to the all pipes. It uses to close the unused pipes.
* @param 3        The quantity of the input commands lines.
* @param 4        A double pointer to the command argument.
*
* @return         return 1 if the command cant be executed.
*/int first_child(int ch1_to_ch2[],int **pipes, int lines, char **command_arguments);

/**
* @brief          This function is responsable of the middel childs. It execut the
*                 all commands exept the first and the last and write the result in the given pipe.
* @param 1        The pipe to read the previous executed command from.
* @param 2        The pipe to write the result in for the next child.
* @param 3        A pointer to the all pipes. It uses to close the unused pipes.
* @param 4        The quantity of the input commands lines.
* @param 5        A double pointer to the command argument.
*
* @return         return 1 if the command cant be executed.
*/int between_child(int ch1_to_ch2[], int ch2_to_ch3[],
                   int **pipes,int lines,char **command_arguments);

/**
* @brief          This function is responsable of the last child. It execut the
*                 last command and write the result in stdout.
* @param 1        The pipe to read the previous executed commands from.
* @param 2        A pointer to the all pipes. It uses to close the unused pipes.
* @param 3        The quantity of the input commands lines.
* @param 4        A double pointer to the command argument.
*
* @return         return 1 if the command cant be executed.
*/int last_child(int ch2_to_ch3[],int **pipes,int lines,char **command_arguments);

/**
* @brief          This function calls when there is just on line command.
* @param 1        A double pointer to the command arguments
* @return         return 1 if the command cant be executed and 0 if it can.
*/int one_line_child (char **list_of_commands);

#endif
