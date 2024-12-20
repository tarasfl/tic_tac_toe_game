/*******************************************************************************
* Title                 :   Easy Bot file
* Filename              :   easy_bot.c
* Author                :   TMF
* Origin Date           :   18/11/2024
* Version               :   1.0.0
* Compiler              :   GNU GCC Compiler
* Target                :   i686-w64-mingw32
* Notes                 :   Easy bots for 3x3 and 4x4 boards
*******************************************************************************/

#include <stdlib.h>
#include <time.h>

// Function Prototypes
int bot_move(char board[]);
char bot_move_4x4(char board[]);

// Function for the easy 3x3 bot's random move
int bot_move(char board[]) {
    srand(time(NULL)); // Seed the random number generator

    int move;
    do {
        move = rand() % 9 + 1; // Generate a number between 1 and 9
    } while (board[move] != '1' + (move - 1)); // Ensure the move is valid

    return move; // Return the bot's move
}
// Function for the easy 4x4 bot's random move
char bot_move_4x4(char board[]) {
    srand(time(NULL)); // Seed the random number generator

    int indx;
    do {
        indx = rand() % 16 + 1; // Generate a random index between 1 and 16
    } while (board[indx] != '1' + (indx - 1) &&
             !(indx >= 10 && indx <= 16 && board[indx] == 'A' + (indx - 10)));
    // Ensure the move is valid (numeric or alphabetic positions)

    return board[indx]; // Return the character in the selected position
}

