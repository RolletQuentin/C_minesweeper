/*!
\file main.c
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief Vectors and matrix manipulations
*/

#define ERROR_MISSING_VALUE -1
#define ERROR_VALUE_OUT_OF_RANGE -2
#define ERROR_NO_NUMBER -3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "usefull_functions.h"
#include "deminor.h"

/*!
\fn int main(int argc, char **argv)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 15/11/2022
\brief main function - print a menu to use functions
\param argc number of arguments
\param **argv values of arguments
\return 0 if all is good
*/
int main(int argc, char **argv)
{
    printf("Welcome to the minesweeper !\n");

    playGame();
 
    // because all is good
    return (0);
}