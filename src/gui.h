#ifndef __GUI_H_
#define __GUI_H_

#include <unistd.h>
#include <time.h>
#include <gtk/gtk.h>
#include "deminor.h"

/*!
\fn void discoverCase(boardCase bc_case)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To discover hidden info of the case. You can put a flag or discover the case.
\param bc_case the case clicked by the player
*/
void discoverCase(boardCase bc_case);

/*!
\fn void updateFlags(int int_totalNumberOfFlags, int int_numberOfFlags, GtkWidget *p_label)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To update the print of the number of flags put by the player.
\param int_totalNumberOfFlags correspond to the number of mines
\param int_numberOfFlags correspond to the number of flags
\param *p_label the widget link to the print of number of flags
*/
void updateFlags(int int_totalNumberOfFlags, int int_numberOfFlags, GtkWidget *p_label);

/*!
\fn void updateTime(long int lint_milliseconds, GtkWidget *p_label)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To update the print of the timer.
\param lint_milliseconds the number of milliseconds since the begining of the game
\param *p_label the widget link to the print of number of flags
*/
void updateTime(long int lint_milliseconds, GtkWidget *p_labelTime);

/*!
\fn void playPrint(GtkWidget *p_button, GdkEventButton *p_event, struct gameData *p_data)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To play one time and actualize the board.
\param *p_button the button link to the case
\param *p_event the event occur when you click on the button
\param *p_data the data relative to the board game
*/
void playPrint(GtkWidget *p_button, GdkEventButton *p_event, struct gameData *p_data);

/*!
\fn void mainPrint(int argc, char **argv)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To initialize Gtk and print the first window we see at the start of the program.
\param argc the number of arguments pass in the main function
\param **argv the arguments pass in the main function
*/
void mainPrint(int argc, char **argv);

/*!
\fn void createGridBoard(boardCase **ttbc_board, GtkWidget *p_tableBoard, int int_numberOfLines, int int_numberOfColumns)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To create the grid to play the game.
\param **ttbc_board the board the game
\param *p_tableBoard the container of the board game
\param int_numberOfLines the number of lines of the board
\param int_numberOfColumns the number of columns of the board
*/
void createGridBoard(boardCase **ttbc_board, GtkWidget *p_tableBoard, int int_numberOfLines, int int_numberOfColumns);

/*!
\fn void showGame(GtkWidget *widget, struct gameData *p_data)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To show the game screen.
\param *widget the last button we click associated to this function
\param *p_data the data relative to the game
*/
void showGame(GtkWidget *widget, struct gameData *p_data);

/*!
\fn void showRules(GtkWidget *widget, gpointer data)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To show the rules.
\param *widget the last button we clicked associated to this function
\param data some data
*/
void showRules(GtkWidget *widget, gpointer data);

/*!
\fn void goBackMenu(GtkWidget *widget, gpointer data)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 30/12/2022
\brief To print the main menu.
\param *widget the last button we clicked associated to this function
\param data some data
*/
void goBackMenu(GtkWidget *widget, gpointer data);

void pauseGame(GtkWidget *widget, gpointer data);

void resumeGame(GtkWidget *widget, gpointer data);

void resetGame(GtkWidget *widget, gpointer data);

void changeDifficultyGame(GtkWidget *widget, gpointer data);

#endif