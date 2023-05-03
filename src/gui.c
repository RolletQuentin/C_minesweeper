/*!
\file gui.c
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 18/12/2022
\brief To have a nice GUI for the minesweeper game
*/

#include "gui.h"

void mainPrint(int argc, char **argv)
{
    // Variables
    GtkWidget *p_window;      // the main window
    GtkWidget *p_labelTitle;  // the main title
    GtkWidget *p_buttonPlay;  // to play a game
    GtkWidget *p_buttonRules; // to show the rules
    GtkWidget *p_boxMenu;     // the frame menu
    GtkWidget *p_boxMain;     // the main frame
    struct gameData *p_data;  // game data for all the game. This data is updated each times we discover a case

    // Initialization of gtk
    gtk_init(&argc, &argv);

    // Creation and configuration of the main window
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(p_window), 720, 360);
    gtk_window_set_title(GTK_WINDOW(p_window), "Minesweeper");

    // Connection to "destroy" signal of the window
    g_signal_connect(G_OBJECT(p_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // creation of the main container
    p_boxMain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    p_boxMenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // creation of the main title
    p_labelTitle = gtk_label_new("Minesweeper");
    // gtk_label_set_use_markup(GTK_LABEL(p_labelTitle), TRUE);

    // creation of the button
    p_buttonPlay = gtk_button_new_with_label("Play");
    p_buttonRules = gtk_button_new_with_label("Rules");

    // Creation of the data
    p_data = malloc(sizeof(struct gameData *) * sizeof(struct gameData *));
    p_data->int_numberOfLines = 10;
    p_data->int_numberOfColumns = 10;
    p_data->int_numberOfMines = 10;
    p_data->int_numberOfFlags = 0;
    p_data->p_boxMain = p_boxMain;
    p_data->p_boxMenu = p_boxMenu;

    // set the connection of the buttons
    g_signal_connect(G_OBJECT(p_buttonPlay), "clicked", G_CALLBACK(showGame), p_data);
    g_signal_connect(G_OBJECT(p_buttonRules), "clicked", G_CALLBACK(showRules), p_boxMenu);

    // attach some elements to print the main menu
    gtk_container_add(GTK_CONTAINER(p_window), p_boxMain);
    gtk_container_add(GTK_CONTAINER(p_boxMain), p_boxMenu);
    gtk_container_add(GTK_CONTAINER(p_boxMenu), p_labelTitle);
    gtk_container_add(GTK_CONTAINER(p_boxMenu), p_buttonPlay);
    gtk_container_add(GTK_CONTAINER(p_boxMenu), p_buttonRules);

    // Print the window
    gtk_widget_show_all(p_window);

    // To start the event loop
    gtk_main();
}

void playPrint(GtkWidget *p_button, GdkEventButton *p_event, struct gameData *p_data)
{
    boardCase *bc_case;
    GtkWidget *p_labelVictory;
    int int_win;
    bc_case = g_object_get_data(G_OBJECT(p_button), "boardCase");

    // left click
    if ((p_event->type == GDK_BUTTON_PRESS) && (p_event->button == 1))
    {
        play(p_data->ttbc_board, p_data->int_numberOfLines, p_data->int_numberOfColumns, bc_case->int_row, bc_case->int_column, 1, 1);
    }
    // right click
    else if ((p_event->type == GDK_BUTTON_PRESS) && (p_event->button == 3))
    {
        play(p_data->ttbc_board, p_data->int_numberOfLines, p_data->int_numberOfColumns, bc_case->int_row, bc_case->int_column, 2, 1);

        // update # of flags
        // if there is no flag on the case
        if (bc_case->int_hasFlag == 0)
        {
            p_data->int_numberOfFlags--;
        }
        // there is a flag on the case
        else
        {
            p_data->int_numberOfFlags++;
        }
        updateFlags(p_data->int_numberOfMines, p_data->int_numberOfFlags, p_data->p_labelFlags);
    }

    int_win = win(p_data->ttbc_board, p_data->int_numberOfLines, p_data->int_numberOfColumns);

    if (int_win == 1)
    {
        p_labelVictory = gtk_label_new("Vous avez gagné !");
        gtk_box_pack_end(GTK_BOX(p_data->p_boxInfo), p_labelVictory, TRUE, TRUE, 0);
        gtk_widget_show(p_labelVictory);
    }
}

void updateTime(long int lint_milliseconds, GtkWidget *p_labelTime)
{
    char buffer[30]; // tempory string to use sprintf

    // Add to the buffer the number of milliseconds spent
    sprintf(buffer, "Time : %ld", lint_milliseconds);

    // Update the label
    gtk_label_set_label(GTK_LABEL(p_labelTime), buffer);
}

void updateFlags(int int_totalNumberOfFlags, int int_numberOfFlags, GtkWidget *p_label)
{
    char buffer[30]; // tempory string to use sprintf

    // Add to the buffer the number of milliseconds spent
    sprintf(buffer, "%d / %d 🚩", int_numberOfFlags, int_totalNumberOfFlags);

    // Update the label
    gtk_label_set_label(GTK_LABEL(p_label), buffer);
}

void discoverCase(boardCase bc_case)
{
    char buffer[50]; // buffer to use sprintf

    // Code copying from ChatGPT
    GtkCssProvider *css_provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    // end of copy

    g_print("int_hasFlag = %d\n\n", bc_case.int_hasFlag);

    // the case is not discovered
    if ((bc_case.int_discovered == 0) && (bc_case.int_hasFlag == 0))
    {
        // we change the label and we change the background
        gtk_button_set_label(GTK_BUTTON(bc_case.p_widget), " ");
        gtk_css_provider_load_from_data(css_provider, "button { background-color: grey; }", -1, NULL);
    }

    // the case has a flag
    else if ((bc_case.int_discovered == 0) && (bc_case.int_hasFlag == 1))
    {
        // we change the label and we change the background
        gtk_button_set_label(GTK_BUTTON(bc_case.p_widget), "🚩");
        gtk_css_provider_load_from_data(css_provider, "button { background-color: grey; }", -1, NULL);
    }
    // the case is discovered and ...
    // the case has a mine
    else if (bc_case.int_hasMine == 1)
    {
        // we change the label and we change the background
        gtk_button_set_label(GTK_BUTTON(bc_case.p_widget), "💣");
        gtk_css_provider_load_from_data(css_provider, "button { background-color: white; }", -1, NULL);
    }

    // the case has any information
    else if (bc_case.int_numberOfMines == 0)
    {
        // we change the label and we change the background
        gtk_button_set_label(GTK_BUTTON(bc_case.p_widget), " ");
        gtk_css_provider_load_from_data(css_provider, "button { background-color: white; }", -1, NULL);
    }

    else
    {
        sprintf(buffer, "%d", bc_case.int_numberOfMines);
        // we change the label and we change the background
        gtk_button_set_label(GTK_BUTTON(bc_case.p_widget), buffer);
        gtk_css_provider_load_from_data(css_provider, "button { background-color: white; }", -1, NULL);
    }
}

void createGridBoard(boardCase **ttbc_board, GtkWidget *p_gridBoard, int int_numberOfLines, int int_numberOfColumns)
{
    int int_i; // iteration variable
    int int_j; // iteration variable

    // for each cases of the board
    for (int_i = 0; int_i < int_numberOfLines; int_i++)
    {
        for (int_j = 0; int_j < int_numberOfColumns; int_j++)
        {
            // we attach to the tabme the case and put it at the good place
            gtk_grid_attach(GTK_GRID(p_gridBoard), ttbc_board[int_i][int_j].p_widget, int_i, int_j, 1, 1);
        }
    }
}

void showGame(GtkWidget *widget, struct gameData *p_data)
{
    GtkWidget *p_boxGame;                // the main box game
    GtkWidget *p_boxRightColumn;         // the right column box
    GtkWidget *p_gridBoard;              // the board grid
    GtkWidget *p_boxInfos;               // relative information to the game (# of bombs and time)
    GtkWidget *p_boxMenu;                // menu box
    GtkWidget *p_buttonPause;            // to pause the game
    GtkWidget *p_buttonResume;           // to resume the game
    GtkWidget *p_buttonReset;            // to reset the game with the same configuration
    GtkWidget *p_buttonChangeDifficulty; // to set up new rules (return to the menu)
    GtkWidget *p_labelFlags;             // to show how many flags we have
    GtkWidget *p_labelTime;              // to show the time
    boardCase **ttbc_board;              // the board of the game

    // creeation of the containers
    p_boxGame = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    p_boxRightColumn = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    p_boxInfos = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    p_boxMenu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    p_data->p_boxInfo = p_boxInfos;

    // creation of the board game & update the data
    ttbc_board = init(p_data->int_numberOfLines, p_data->int_numberOfColumns, p_data->int_numberOfMines, 1, p_data);
    p_data->ttbc_board = ttbc_board;
    p_gridBoard = gtk_grid_new();
    createGridBoard(ttbc_board, p_gridBoard, p_data->int_numberOfLines, p_data->int_numberOfColumns);

    // creation of labels & update the data
    p_labelFlags = gtk_label_new("");
    updateFlags(p_data->int_numberOfMines, 0, p_labelFlags);
    p_data->p_labelFlags = p_labelFlags;

    p_labelTime = gtk_label_new("");
    updateTime(0, p_labelTime);
    p_data->p_labelTime = p_labelTime;

    // creation and configuration of buttons
    p_buttonPause = gtk_button_new_with_label("Pause");
    g_signal_connect(G_OBJECT(p_buttonPause), "clicked", G_CALLBACK(pauseGame), NULL);

    p_buttonResume = gtk_button_new_with_label("Reseume");
    g_signal_connect(G_OBJECT(p_buttonResume), "clicked", G_CALLBACK(resumeGame), NULL);

    p_buttonChangeDifficulty = gtk_button_new_with_label("Change difficulty");
    g_signal_connect(G_OBJECT(p_buttonChangeDifficulty), "clicked", G_CALLBACK(changeDifficultyGame), NULL);

    p_buttonReset = gtk_button_new_with_label("Reset");
    g_signal_connect(G_OBJECT(p_buttonReset), "clicked", G_CALLBACK(resetGame), NULL);

    // to hide the previous view
    gtk_widget_hide(GTK_WIDGET(p_data->p_boxMenu));

    // attach widgets to the containers
    gtk_box_pack_start(GTK_BOX(p_boxGame), p_gridBoard, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(p_boxGame), p_boxRightColumn, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(p_boxRightColumn), p_boxInfos, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(p_boxRightColumn), p_boxMenu, TRUE, TRUE, 0);

    gtk_box_pack_end(GTK_BOX(p_boxInfos), p_labelFlags, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(p_boxInfos), p_labelTime, TRUE, TRUE, 0);

    gtk_box_pack_end(GTK_BOX(p_boxMenu), p_buttonPause, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(p_boxMenu), p_buttonReset, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(p_boxMenu), p_buttonChangeDifficulty, TRUE, TRUE, 0);

    // attach the main box to main box
    gtk_container_add(GTK_CONTAINER(p_data->p_boxMain), p_boxGame);

    // print all the widgets
    gtk_widget_show_all(GTK_WIDGET(p_boxGame));
}

void showRules(GtkWidget *widget, gpointer data)
{
    GtkWidget *p_boxRules;
    GtkWidget *p_labelRules;
    GtkWidget *p_buttonReturn;

    p_boxRules = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    p_labelRules = gtk_label_new("Voici les règles du jeu ...");
    p_buttonReturn = gtk_button_new_with_label("Go back menu");

    // connect the button to the callback function
    g_signal_connect(GTK_BUTTON(p_buttonReturn), "clicked", G_CALLBACK(goBackMenu), data);

    // to hide the menu
    gtk_widget_hide(GTK_WIDGET(data));

    // add the rules container to the main container
    gtk_container_add(GTK_CONTAINER(gtk_widget_get_parent(gtk_widget_get_parent(widget))), p_boxRules);

    // add all the widgets to the rules container
    gtk_container_add(GTK_CONTAINER(p_boxRules), p_labelRules);
    gtk_container_add(GTK_CONTAINER(p_boxRules), p_buttonReturn);

    // print the container
    gtk_widget_show_all(GTK_WIDGET(p_boxRules));
}

void goBackMenu(GtkWidget *widget, gpointer data)
{
    // hide widgets
    gtk_widget_hide(GTK_WIDGET(gtk_widget_get_parent(widget)));

    // show the menu
    gtk_widget_show(GTK_WIDGET(data));
}

void pauseGame(GtkWidget *widget, gpointer data)
{
}

void resumeGame(GtkWidget *widget, gpointer data)
{
}

void resetGame(GtkWidget *widget, gpointer data)
{
}

void changeDifficultyGame(GtkWidget *widget, gpointer data)
{
}