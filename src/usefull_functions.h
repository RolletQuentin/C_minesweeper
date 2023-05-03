#ifndef __USEFULL_FUNCTUIONS_H_
#define __USEFULL_FUNCTIONS_H_

#include <stdlib.h>
#include <stdio.h>

#define N 10
#define TABLE_LENGTH 30

/*!
\fn void emptyBuffer()
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 09/11/2022
\brief To make the buffer empty
*/
void emptyBuffer();

/*!
\fn int inputInteger(char *str_message)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 09/11/2022
\brief Ask to the user to input a number
\param char_message The message you want to print before the scanf
\return The int number the user input
*/
int inputInteger(char *str_message);

/*!
\fn int inputStringStatic(char str_text[TABLE_LENGTH])
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 09/11/2022
\brief Ask to the user to input a string with a specify length
\param str_text[TABLE_LENGTH] the string
*/
void inputStringStatic(char str_text[TABLE_LENGTH]);

/*!
\fn void fillIntTable(int *tint_table, int int_length)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief fill a int table with integer
\param tint_table The table we want to fill
\param int_length The length of the table. WARNING : the length must be the same length of the table !
*/
void fillIntTable(int *tint_table, int int_length);

/*!
\fn void fillIntTableAuto(int *tint_table, int int_length, int int_n)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief fill a int table with integer
\param tint_table The table we want to fill
\param int_length The length of the table.
\param int_n the choosen number
*/
void fillIntTableAuto(int *tint_table, int int_length, int int_n);

/*!
\fn void printIntStaticTable(int *tint_table, int int_length)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief print the table
\param tint_table The table we want to print
\param int_length The length of the table. WARNING : the length must be the same length of the table !
*/
void printIntStaticTable(int *tint_table, int int_length);

/*!
\fn void printCharStaticTable(char *tchar_table)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief print the table
\param tchar_table The table we want to print
\param int_length The length of the table. WARNING : the length must be the same length of the table !
*/
void printCharStaticTable(char *tchar_table);

/*!
\fn void rangeIntStaticTable(int *tint_table, int int_length)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief implementation of the range function, id est fill the table from 0 to the length of the table
\param tint_table The table we want to fill
\param int_length The length of the table. WARNING : the length must be the same length of the table !
*/
void rangeIntStaticTable(int *tint_table, int int_length);

/*!
\fn int lengthString(char str_text[TABLE_LENGTH])
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 29/11/2022
\brief get the length of a string
\param str_text a table of chars
\return -1 if the number of chars is too long, else the number of chars
*/
int lengthString(char str_text[TABLE_LENGTH]);

/*!
\fn void swapElementIntTable(int *tint_table, int int_a, int int_b)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 04/12/2022
\brief Swap two elements in a table
\param *tint_table the table where we want to swap the two elements
\param int_a the index of the first element to swap
\param int_b the index of the second element to swap
*/
void swapElementIntTable(int *tint_table, int int_a, int int_b);

/*!
\fn void printIntTable(int *tint_table, int int_length)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 04/12/2022
\brief To print a table.
\param *tint_table the table we want to print
\param int_length the length of the table
*/
void printIntTable(int *tint_table, int int_length);

/*!
\fn void swapElementIntMatrixStatic(int tint_table[N][N], int int_i1, int int_j1, int int_i2, int int_j2)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 04/12/2022
\brief To swap two elements in a static matrix
\param tint_table[N][N] the matrix
\param int_i1 the line index of the first element
\param int_j1 the column index of the first element
\param int_i2 the line index of the second element
\param int_j2 the column index of the second element
*/
void swapElementIntMatrixStatic(int tint_table[N][N], int int_i1, int int_j1, int int_i2, int int_j2);

/*!
\fn int askNumberWithRange(char *str_message, char *str_messageError, int int_min, int int_max)
\author Quentin Rollet <quentin.rollet@cy-tech.fr>
\version 0.1 Initialization
\date 03/12/2022
\brief To ask a number to the user with an allowed range of response.
\param *char_message the print message to notify what the user have to do
\param *char_messageError the print message to notify the error the user have done
\param int_min the minimum of the range
\param int_max the maximum of the range
\return the intput number by the user
*/
int askNumberWithRange(char *str_message, char *str_messageError, int int_min, int int_max);

#endif