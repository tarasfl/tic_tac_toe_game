#include <stdlib.h>
#include <time.h>

// Function for the bot's move
int bot_move(char board[]) {
    srand(time(NULL)); // Seed the random number generator

    int move;
    do {
        move = rand() % 9 + 1; // Generate a number between 1 and 9
    } while (board[move] != '1' + (move - 1)); // Ensure the move is valid

    return move; // Return the bot's move
}

