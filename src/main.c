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
#include "gui.h"

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
    int int_choice; // choice to choose the version og the deminor

    printf("Bienvenue dans le démineur !\n");

    int_choice = askNumberWithRange("Veuillez choisir la version du jeu :\n\t1 -- Démineur en console (fonctionnel)\n\t2 -- Démineur en fenêtre (ne fonctionne pas à tout les coups et n'est pas totalement terminé, c'est juste comme ça..)\n", "Merci de renseigner un entier entre 1 et 2\n", 1, 2);

    switch (int_choice)
    {
    case 1:
        playGame();
        break;

    case 2:
        mainPrint(argc, argv);
        break;

    default:
        fprintf(stderr, "Une erreur inconnue s'est produite, merci de relancé le programme.\n");
        exit(-1);
        break;
    }

    // because all is good
    return (0);
}