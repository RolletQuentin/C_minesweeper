/*!
\file deminor.c
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 08/12/2022
\brief To play deminor game
*/

#include "deminor.h"
#include "gui.h"

void printBoardGame(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns)
{
    int int_i; // iteration variable
    int int_j; // iteration variable

    // to clear the console
    system("clear");

    // first line (column index)
    TABULATION;
    printf("  ");
    for (int_j = 0; int_j < int_numberOfColumns; int_j++)
    {
        printf("  %d ", int_j);
    }
    printf("\n");

    // middle lines
    for (int_i = 0; int_i < int_numberOfLines; int_i++)
    {
        // top line
        TABULATION;
        printf("  ");
        for (int_j = 0; int_j < int_numberOfColumns; int_j++)
        {
            printf("+---");
        }
        printf("+\n");

        // number line
        TABULATION;
        printf("%d ", int_i);
        // print each cases
        for (int_j = 0; int_j < int_numberOfColumns; int_j++)
        {
            // if player use a flag
            if (ttbc_board[int_i][int_j].int_hasFlag == 1)
            {
                printf("| F ");
            }
            // the case isn't discoverd
            else if (ttbc_board[int_i][int_j].int_discovered == 0)
            {
                printf("| # ");
            }
            // the case is discovered and there is a mine
            else if ((ttbc_board[int_i][int_j].int_discovered == 1) && (ttbc_board[int_i][int_j].int_hasMine == 1))
            {
                printf("| X ");
            }
            // the case is discoverd and there is no mine next to the case
            else if ((ttbc_board[int_i][int_j].int_discovered == 1) && (ttbc_board[int_i][int_j].int_numberOfMines == 0))
            {
                printf("| . ");
            }
            // the case is discovered and there are mines next to the case
            else
            {
                printf("| %d ", ttbc_board[int_i][int_j].int_numberOfMines);
            }
        }
        printf("|\n");
    }

    // last line
    TABULATION;
    printf("  ");
    for (int_j = 0; int_j < int_numberOfColumns; int_j++)
    {
        printf("+---");
    }
    printf("+\n\n");
}

boardCase **init(int int_numberOfLines, int int_numberOfColumns, int int_numberOfMines, int int_gtk, struct gameData *p_data)
{
    // create the seed to random generator
    srand(time(NULL));

    int int_i;                // iteration variable
    int int_j;                // iteration variable
    boardCase **ttbc_board;   // board of the game
    boardCase bc_initialCase; // initial case
    GtkCssProvider *p_cssProvider;
    GdkDisplay *p_display;
    GdkScreen *p_screen;

    if (int_gtk == 1)
    {
        // code copying from chatGPT to change the color of the buttons, in case where we have a gui
        p_cssProvider = gtk_css_provider_new();
        p_display = gdk_display_get_default();
        p_screen = gdk_display_get_default_screen(p_display);
        gtk_style_context_add_provider_for_screen(p_screen, GTK_STYLE_PROVIDER(p_cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        // end of the copy
    }

    // creation of the table with memory allocation
    ttbc_board = malloc(int_numberOfLines * sizeof(boardCase *) * sizeof(boardCase *));

    for (int_i = 0; int_i < int_numberOfLines; int_i++)
    {
        ttbc_board[int_i] = malloc(int_numberOfColumns * sizeof(boardCase) * sizeof(boardCase));
    }

    // initialization of the initial case
    bc_initialCase.int_discovered = 0;
    bc_initialCase.int_hasFlag = 0;
    bc_initialCase.int_hasMine = 0;
    bc_initialCase.int_numberOfMines = 0;

    // initialization of the board game with the initial case
    for (int_i = 0; int_i < int_numberOfLines; int_i++)
    {
        for (int_j = 0; int_j < int_numberOfColumns; int_j++)
        {
            ttbc_board[int_i][int_j] = bc_initialCase;
            ttbc_board[int_i][int_j].int_row = int_i;
            ttbc_board[int_i][int_j].int_column = int_j;

            // we have a gui
            if (int_gtk == 1)
            {
                // creation of the button associated to the case
                ttbc_board[int_i][int_j].p_widget = gtk_button_new_with_label(" ");
                gtk_css_provider_load_from_data(p_cssProvider, "button { background-color: grey; }", -1, NULL);
                g_object_set_data(G_OBJECT(ttbc_board[int_i][int_j].p_widget), "boardCase", &ttbc_board[int_i][int_j]);

                // connect the button when this one is pressed (left or right click) and play
                g_signal_connect(G_OBJECT(ttbc_board[int_i][int_j].p_widget), "button-press-event", G_CALLBACK(playPrint), p_data);
            }
        }
    }

    // we add randomly mines in the board game while no mines remaining
    while (int_numberOfMines != 0)
    {
        int_i = rand() % int_numberOfLines;
        int_j = rand() % int_numberOfColumns;

        // if there is no mine in the case
        if (ttbc_board[int_i][int_j].int_hasMine == 0)
        {
            int_numberOfMines--;
            ttbc_board[int_i][int_j].int_hasMine = 1;
        }
    }

    // calculation of the number of mines next to the case
    for (int_i = 0; int_i < int_numberOfLines; int_i++)
    {
        for (int_j = 0; int_j < int_numberOfColumns; int_j++)
        {
            // top
            if ((int_i != 0) && (ttbc_board[int_i - 1][int_j].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
            // bottom
            if ((int_i != int_numberOfLines - 1) && (ttbc_board[int_i + 1][int_j].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
            // left
            if ((int_j != 0) && (ttbc_board[int_i][int_j - 1].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
            // right
            if ((int_i != int_numberOfColumns - 1) && (ttbc_board[int_i][int_j + 1].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
            // top left
            if ((int_i != 0) && (int_j != 0) && (ttbc_board[int_i - 1][int_j - 1].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
            // top right
            if ((int_i != 0) && (int_j != int_numberOfColumns - 1) && (ttbc_board[int_i - 1][int_j + 1].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
            // bottom left
            if ((int_i != int_numberOfLines - 1) && (int_j != 0) && (ttbc_board[int_i + 1][int_j - 1].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
            // bottom right
            if ((int_i != int_numberOfLines - 1) && (int_j != int_numberOfColumns - 1) && (ttbc_board[int_i + 1][int_j + 1].int_hasMine == 1))
            {
                ttbc_board[int_i][int_j].int_numberOfMines++;
            }
        }
    }

    return (ttbc_board);
}

void discover(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns, int int_i, int int_j, int int_gtk)
{
    if (ttbc_board[int_i][int_j].int_discovered == 0)
    {
        ttbc_board[int_i][int_j].int_discovered = 1;
        // if we have a gui, we have to change the case
        if (int_gtk == 1)
        {
            discoverCase(ttbc_board[int_i][int_j]);
        }

        // we don't have information with this case, so we discover the next cases
        if (ttbc_board[int_i][int_j].int_numberOfMines == 0)
        {

            // top
            if (int_i != 0)
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i - 1, int_j, int_gtk);
            }
            // bottom
            if (int_i != int_numberOfLines - 1)
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i + 1, int_j, int_gtk);
            }
            // left
            if (int_j != 0)
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i, int_j - 1, int_gtk);
            }
            // right
            if (int_i != int_numberOfColumns - 1)
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i, int_j + 1, int_gtk);
            }
            // top left
            if ((int_i != 0) && (int_j != 0))
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i - 1, int_j - 1, int_gtk);
            }
            // top right
            if ((int_i != 0) && (int_j != int_numberOfColumns - 1))
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i - 1, int_j + 1, int_gtk);
            }
            // bottom left
            if ((int_i != int_numberOfLines - 1) && (int_j != 0))
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i + 1, int_j - 1, int_gtk);
            }
            // bottom right
            if ((int_i != int_numberOfLines - 1) && (int_j != int_numberOfColumns - 1))
            {
                discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_i + 1, int_j + 1, int_gtk);
            }
        }
    }
}

int win(boardCase **ttbc_board, int int_numerOfLines, int int_numberOfColumns)
{
    int int_i;      // itteration variable
    int int_j;      // itteration variable
    int int_result; // 1 if the player win, 0 else

    int_result = 1;

    for (int_i = 0; int_i < int_numerOfLines; int_i++)
    {
        for (int_j = 0; int_j < int_numberOfColumns; int_j++)
        {
            // if we have a case without mine but isn't discovered, the player doesn't win
            if ((ttbc_board[int_i][int_j].int_hasMine == 0) && (ttbc_board[int_i][int_j].int_discovered == 0))
            {
                int_result = 0;
            }
        }
    }

    return (int_result);
}

int play(boardCase **ttbc_board, int int_numberOfLines, int int_numberOfColumns, int int_line, int int_column, int int_choice, int int_gtk)
{
    int int_result; // -1 if an error is occur, 0 if there is no mine on the case, 1 if a mine is discovered
    int int_confirm;

    int_result = 0;

    // out of bounds
    if ((int_column < 0) || (int_column > int_numberOfColumns - 1))
    {
        fprintf(stderr, "Merci de saisir un entier entre 0 et %d.\n", int_numberOfColumns - 1);
        int_result = -1;
    }
    else if ((int_line < 0) || (int_line > int_numberOfLines - 1))
    {
        fprintf(stderr, "Merci de saisir un entier entre 0 et %d.\n", int_numberOfLines - 1);
        int_result = -1;
    }
    // the case is already discovered
    else if (ttbc_board[int_line][int_column].int_discovered == 1)
    {
        fprintf(stderr, "La case est déjà découverte. Merci de sélectionner une case qui n'est pas encore découverte.\n");
        int_result = -1;
    }
    // we want to discover the case and this one don't have a flag on it
    else if ((int_choice == 1) && (ttbc_board[int_line][int_column].int_hasFlag == 0))
    {
        // we discover a new case because the case doesn't have a flag
        discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_line, int_column, int_gtk);

        // we verify if we touch a mine or not
        if (ttbc_board[int_line][int_column].int_hasMine == 1)
        {
            int_result = 1;
        }
    }
    // we want to discover a case but this one has a flag
    else if ((int_choice == 1) && (ttbc_board[int_line][int_column].int_hasFlag == 1))
    {
        // we discover a new case but we ask confirmation because there is a flag
        int_confirm = askNumberWithRange("Il y a un drapeau sur cette case. Etes-vous sûr de vouloir la découvrir ? (1: oui, 0: non)", "Merci de renseigner un entier entre 0 et 1", 0, 1);
        if (int_confirm == 1)
        {
            ttbc_board[int_line][int_column].int_hasFlag = 0;
            discover(ttbc_board, int_numberOfLines, int_numberOfColumns, int_line, int_column, int_gtk);

            // we verify if we touch a mine or not
            if (ttbc_board[int_line][int_column].int_hasMine == 1)
            {
                int_result = 1;
            }
        }
        else
        {
            int_result = -1;
        }
    }
    // we want to put a flag
    else if (ttbc_board[int_line][int_column].int_hasFlag == 0)
    {
        // we put a flag
        ttbc_board[int_line][int_column].int_hasFlag = 1;
        if (int_gtk == 1)
        {
            discoverCase(ttbc_board[int_line][int_column]);
        }
    }
    // we want to pop a flag
    else
    {
        // we delete the flag
        ttbc_board[int_line][int_column].int_hasFlag = 0;
        {
            discoverCase(ttbc_board[int_line][int_column]);
        }
    }

    return (int_result);
}

void playGame()
{
    int int_numberOfMines;   // number of mines in the board
    int int_numberOfLines;   // number of lines of the board
    int int_numberOfColumns; // number of columns of the board
    int int_result;          // 1 if a mine is discovered, -1 if an error is occur, 0 else
    int int_line;            // the line the player want discover
    int int_column;          // the column the player want discover
    int int_choice;          // the choice between discover the case or put a flag
    time_t time_start;       // the time at the start of the game
    time_t time_end;         // the final time of the game
    int int_time;            // the time in seconds of the game
    boardCase **ttbc_board;  // the board game
    int int_i;               // iteration variable
    int int_j;               // iteration variable
    int int_gtk;             // if we want to play with graphical interface or not

    // Ask the rules to the player
    int_numberOfLines = inputInteger("Avec combien de lignes voulez-vous jouez ?\n");
    int_numberOfColumns = inputInteger("Avec combien de colonnes voulez-vous jouez ?\n");
    int_numberOfMines = askNumberWithRange("Avec combien de mines voulez-vous jouez ?\n", "Veuillez renseigner un entier.\n", 1, int_numberOfColumns * int_numberOfLines);

    // initialization of variables
    int_result = 0;
    int_gtk = 0;
    int_time = 0;
    time_start = time(NULL);

    // initialization of the board game
    ttbc_board = init(int_numberOfLines, int_numberOfColumns, int_numberOfMines, 0, NULL);

    // win condition : all case with no mines is discovered & no mines is discovered
    while ((int_result == 0) && (win(ttbc_board, int_numberOfLines, int_numberOfColumns) == 0))
    {
        printBoardGame(ttbc_board, int_numberOfLines, int_numberOfColumns);

        // while the player give a right command to play
        do
        {
            int_line = askNumberWithRange("Ligne ?\n", "Veillez renseigner un entier.\n", 0, int_numberOfLines - 1);
            int_column = askNumberWithRange("Colonne ?\n", "Veillez renseigner un entier.\n", 0, int_numberOfColumns - 1);
            int_choice = askNumberWithRange("Découvrir (1) / Drapeau (2)\n", "Veillez renseigner un entier.\n", 1, 2);
            int_result = play(ttbc_board, int_numberOfLines, int_numberOfColumns, int_line, int_column, int_choice, int_gtk);
        } while (int_result == -1);
    }

    // the game is finished
    time_end = time(NULL);
    int_time = time_end - time_start;

    // a mine is dicovered
    if (int_result == 1)
    {
        // we discover all the bomb and delete all the flags
        for (int_i = 0; int_i < int_numberOfLines; int_i++)
        {
            for (int_j = 0; int_j < int_numberOfColumns; int_j++)
            {
                if (ttbc_board[int_i][int_j].int_hasFlag == 1)
                {
                    ttbc_board[int_i][int_j].int_hasFlag = 0;
                }
                if (ttbc_board[int_i][int_j].int_hasMine == 1)
                {
                    ttbc_board[int_i][int_j].int_discovered = 1;
                    printBoardGame(ttbc_board, int_numberOfLines, int_numberOfColumns);
                    usleep(rand() % 100000);
                }
            }
        }
        printf("Vous avez rencontré une mine. Vous avez perdu.\nVotre partie a durrée %d secondes.\n", int_time);
    }
    else
    {
        printBoardGame(ttbc_board, int_numberOfLines, int_numberOfColumns);
        printf("Bravo ! Vous avez gagné !\nVotre partie a durrée %d secondes.\n", int_time);
    }

    // free memory
    for (int_i = 0; int_i < int_numberOfLines; int_i++)
    {
        free(ttbc_board[int_i]);
    }
    free(ttbc_board);
}