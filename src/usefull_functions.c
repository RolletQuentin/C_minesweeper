/*!
\file usefull_functions.c
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief Many different useful functions
*/

#include "usefull_functions.h"

/* -------------------------------- EMPTY BUFFER METHOD -------------------------------- */

void emptyBuffer()
{
    char char_c; // to make the buffer empty
    do
    {
        scanf("%c", &char_c);
    } while (char_c != '\n');
}

/* -------------------------------- INPUT METHODS -------------------------------- */

int inputInteger(char *str_message)
{
    int int_inputNumber; // input integer
    int int_result;      // result of scanf
    int int_error;       // -1 if an error is occur

    // while the user input a right number
    do
    {
        int_error = 0;

        printf("%s", str_message);
        int_result = scanf("%d", &int_inputNumber);
        emptyBuffer();

        // test if scanf worked
        if (int_result == 0)
        {
            // scanf doesn't work -> print input error
            fprintf(stderr, "Erreur de saisie : Merci de renseigner un entier.\n");
            int_error = -1;
        }
    } while (int_error == -1);

    return (int_inputNumber);
}

void inputStringStatic(char str_text[TABLE_LENGTH])
{
    int int_result; // result of scanf
    int int_error;  // -1 if an error is occur

    // while the user input a right number
    do
    {
        int_error = 0;

        int_result = scanf("%[^\n]", str_text);
        emptyBuffer();

        // test if scanf worked
        if ((int_result == 0) || (lengthString(str_text) == -1))
        {
            // scanf doesn't work -> print input error
            fprintf(stderr, "Erreur de saisie : Merci de renseigner une chaîne de caractère de longueur inférieure à %d.\n", TABLE_LENGTH - 1);
            int_error = -1;
        }
    } while (int_error == -1);
}

int askNumberWithRange(char *str_message, char *str_messageError, int int_min, int int_max)
{
    int int_error;
    int int_selector;

    // ask a number and verify if this one isn't out of range
    do
    {
        int_error = 0;
        int_selector = inputInteger(str_message);
        if ((int_selector < int_min) || (int_selector > int_max))
        {
            fprintf(stderr, "%s", str_messageError);
            int_error = -1;
        }
    } while (int_error == -1);

    return (int_selector);
}

/* -------------------------------- TABLE METHODS -------------------------------- */

void fillIntTable(int *tint_table, int int_length)
{
    int int_i; // iteration variable

    // for each case, we ask the value of the case
    for (int_i = 0; int_i < int_length; int_i++)
    {
        tint_table[int_i] = inputInteger("Entier de la case i : ");
    }
}

void fillIntTableAuto(int *tint_table, int int_length, int int_n)
{
    int int_i; // iteration variable

    // for each case, we ask the value of the case
    for (int_i = 0; int_i < int_length; int_i++)
    {
        tint_table[int_i] = int_n;
    }
}

void printIntStaticTable(int *tint_table, int int_length)
{
    int int_i; // iteration variable

    printf("[");

    // we print each case of the table
    for (int_i = 0; int_i < (int_length - 1); int_i++)
    {
        printf("%d,", tint_table[int_i]);
    }

    printf("%d]\n", tint_table[int_length - 1]);
}

void printCharStaticTable(char *tchar_table)
{
    int int_i; // iteration variable
    int int_stringLength;

    int_stringLength = lengthString(tchar_table);

    if (int_stringLength == -1)
    {
        fprintf(stderr, "Erreur lors de l'affichage de la chaine.");
        exit(-1);
    }
    else
    {
        // we print each case of the table
        for (int_i = 0; int_i < int_stringLength; int_i++)
        {
            printf("%c", tchar_table[int_i]);
        }
    }
}

void rangeIntStaticTable(int *tint_table, int int_length)
{
    int int_i; // iteration variable

    // for each case, we put the value of i in the case
    for (int_i = 0; int_i < int_length; int_i++)
    {
        tint_table[int_i] = int_i;
    }
}

int lengthString(char str_text[TABLE_LENGTH])
{
    int int_length; // length of the string
    int int_error;  // equals to -1 if an error is occur

    int_error = -1;
    int_length = 0;

    // first condition to not have infinity loop, the second is indeed : while we doesn't see \0
    while ((int_length < TABLE_LENGTH) && (int_error == -1))
    {
        if (str_text[int_length] == '\0')
        {
            int_error = 0;
        }
        else
        {
            int_length++;
        }
    }

    if (int_error == -1)
    {
        return (-1);
    }
    else
    {
        return (int_length);
    }
}

void swapElementIntMatrixStatic(int ttint_table[N][N], int int_i1, int int_j1, int int_i2, int int_j2)
{
    int int_tmp; // tempory variable

    int_tmp = ttint_table[int_i1][int_j1];
    ttint_table[int_i1][int_j1] = ttint_table[int_i2][int_j2];
    ttint_table[int_i2][int_j2] = int_tmp;
}

/* -------------------------------- TABLE DYNAMIC METHODS -------------------------------- */

void swapElementIntTable(int *tint_table, int int_a, int int_b)
{
    int int_tmp; // tempory variable

    int_tmp = tint_table[int_a];
    tint_table[int_a] = tint_table[int_b];
    tint_table[int_b] = int_tmp;
}

void printIntTable(int *tint_table, int int_length)
{
    int int_i; // iteration variable

    printf("[");

    // we print each case of the table
    for (int_i = 0; int_i < (int_length - 1); int_i++)
    {
        printf("%d,", tint_table[int_i]);
    }

    printf("%d]\n", tint_table[int_length - 1]);
}
