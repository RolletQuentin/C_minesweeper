#ifndef __DEMINOR_H_
#define __DEMINOR_H_

#define TABULATION printf("          ")

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <gtk/gtk.h>
#include "usefull_functions.h"

/*! \struct boardCase
 * Case of the board.
 */
typedef struct
{
    int int_discovered;    /*!< 0 if the case isn't discoverd, else 1 */
    int int_hasMine;       /*!< 0 if the case doesn't have a mine, else 1 */
    int int_numberOfMines; /*!< number of next cases with a mine */
    int int_hasFlag;       /*!< 0 if the case doesn't have a flag, else 1*/
    GtkWidget *p_widget;   /*!< the widget linked to the case*/
    int int_row;           /*!< the row of the case*/
    int int_column;        /*!< the colum of the case*/
} boardCase;

/*! \struct gameData
 * Some data relative to the game
 */
struct gameData
{
    boardCase **ttbc_board;   /*!< the board og the game */
    boardCase bc_currentCase; /*!< the last case clicked */
    int int_numberOfLines;    /*!< the number of lines of the board game */
    int int_numberOfColumns;  /*!< the number of columns of the board game */
    int int_numberOfMines;    /*!< the total number of mines in the board game (hidden or not)*/
    int int_numberOfFlags;    /*!< the number of flags play by the player*/
    GtkWidget *p_boxMain;     /*!< the main box of the gtk window (main container) */
    GtkWidget *p_boxMenu;     /*!< the box menu (where you have some buttons to pause the game for example)*/
    GtkWidget *p_boxInfo;     /*!< the box info (where you have the timer and the flag's counter)*/
    GtkWidget *p_labelFlags;  /*!< the label link to the counter of flags*/
    GtkWidget *p_labelTime;   /*!< the label link to the timer*/
};

/*!
\fn void printBoardGame(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 08/12/2022
\brief To print the board game.
\param **ttbc_board the board
\param int_numberOfLines number of lines of the board
\param int_numberOfColumns number of columns of the board
*/
void printBoardGame(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns);

/*!
\fn boardCase **init(int int_numberOfLines, int int_numberOfColumns, int int_numberOfMines, int int_gtk, struct gameData *p_data)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 08/12/2022
\brief init the board with mines
\param int_numberOfLines number of lines of the board
\param int_numberOfColumns number of columns of the board
\param int_numberOfMines number of mines
\param int_gtk 0 if we don't have gui, 1 else
\param *p_data a pointer to data relative to the game
\return the board
*/
boardCase **init(int int_numberOfLines, int int_numberOfColumns, int int_numberOfMines, int int_gtk, struct gameData *p_data);

/*!
\fn void discover(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns, int int_i, int int_j, int int_gtk)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 18/12/2022
\brief To update the board and discover a case when this one is selected
\param **ttbc_board the board game
\param int_numberOfLines the number of lines of the board game
\param int_numberOfColumns the number of columns of the board game
\param int_i the line of the case selected
\param int_j the column of the case selected
\param int_gtk 0 if we don't have gui, 1 else
*/
void discover(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns, int int_i, int int_j, int int_gtk);

/*!
\fn int play(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns, int int_line, int int_column, int int_choice, int int_gtk)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 18/12/2022
\brief To play one iteration of the game.
\param **ttbc_board the board game
\param int_numberOfLines the number of lines of the board game
\param int_numberOfColumns the number of columns of the board game
\param int_line the line of the case selected
\param int_column the column of the case selected
\param int_choice 1 to discover a case, 2 to put a flag
\param int_gtk 0 if we don't have gui, 1 else
\return 0 if nothing happend, -1 if an error is occur, 1 if the player lose the game
*/
int play(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns, int int_line, int int_column, int int_choice, int int_gtk);

/*!
\fn void playGame()
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 18/12/2022
\brief Start a new game with command lines
*/
void playGame();

/*!
\fn int win(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To verify if you have a win board or not.
\param **ttbc_board the board relative to the game
\param int_numberOfLines the number of lines of the board game
\param int_numberOfColumns the number of columns of the board game
\return 1 if the player win, 0 else*/
int win(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns);

#endif