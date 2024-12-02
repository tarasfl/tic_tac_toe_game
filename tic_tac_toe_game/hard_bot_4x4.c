#include <stdio.h>
#include "easy_bot.h"


char board[4][4];

int max_4x4(int a, int b) {
    return (a > b) ? a : b;
}

int min_4x4(int a, int b) {
    return (a < b) ? a : b;
}

void translate_to_board_4x4(char board[4][4], char num[17]) {
    for (int i = 0; i < 16; i++) {
        int row = i / 4;
        int col = i % 4;
        board[row][col] = num[i + 1]; // +1 because `num` starts at index 1
    }
}

void translate_to_one_array_4x4(char num[17], char board[4][4]) {
    for (int i = 0; i < 17; i++) {
        int row = i / 4;
        int col = i % 4;
        num[i + 1] = board[row][col]; // +1 because `num` starts at index 1
    }
}

int isMovesLeft_4x4(char board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 1;
            }
        }
    }
    return 0;
}

// Function to evaluate the board
int evaluate_4x4(char board[4][4], char opponent_symb) {
    char comp_symb = (opponent_symb=='X') ? 'O': 'X';
    // Check rows for victory
    for (int row = 0; row < 4; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][2] == board[row][3]) {
            if (board[row][0] == comp_symb) {
                return 10;
            } else if (board[row][0] == opponent_symb) {
                return -10;
            }
        }
    }

    // Check columns for victory
    for (int col = 0; col < 4; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[2][col] == board[3][col] ) {
            if (board[0][col] == comp_symb) {
                return 10;
            } else if (board[0][col] == opponent_symb) {
                return -10;
            }
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] == board[3][3]) {
        if (board[0][0] == comp_symb) {
            return 10;
        } else if (board[0][0] == opponent_symb) {
            return -10;
        }
    }

    if (board[0][3] == board[1][2] && board[1][2] == board[2][1] && board[2][1] == board[3][0]) {
        if (board[0][3] == comp_symb) {
            return 10;
        } else if (board[0][3] == opponent_symb) {
            return -10;
        }
    }

    return 0; // No winner
}

// Minimax function
int minimax_4x4(char board[4][4], int depth, int isMax, int alpha, int beta,  char opponent_symb) {
    int score = evaluate_4x4(board, opponent_symb);

    // If the computer has won
    if (score == 10)
        return score - depth; // Depth penalizes longer paths to victory

    // If the opponent has won
    if (score == -10)
        return score + depth; // Depth penalizes longer paths to defeat

    // If no moves are left, it's a draw
    if (!isMovesLeft_4x4(board))
        return 0;

    // Depth limit to prevent stack overflow
    if (depth > 10)
        return 0;

    char comp_symb = (opponent_symb == 'X') ? 'O' : 'X';

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = comp_symb;
                    int value = minimax_4x4(board, depth + 1, !isMax, alpha, beta, opponent_symb);
                    best = max_4x4(best, value);
                    alpha = max_4x4(best, alpha);
                    board[i][j] = backup; // Undo move
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = opponent_symb;
                    int value = minimax_4x4(board, depth + 1, !isMax, alpha, best, opponent_symb);
                    best = min_4x4(best, value);
                    beta = min_4x4(best, beta);
                    board[i][j] = backup; // Undo move
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the player
int findBestMove_4x4(char board[4][4], int* bestRow, int* bestCol, char opponent_symb) {
    int bestVal = -1000; // Initialize the best value
    *bestRow = -1;
    *bestCol = -1;

    // Loop through all possible moves
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Check if the current cell is available
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                // Backup the original value
                char backup = board[i][j];

                // Make the move
                board[i][j] = (opponent_symb == 'X') ? 'O' : 'X'; // Assume the AI is playing opposite of opponent

                // Evaluate the move
                int moveVal = minimax_4x4(board, 0, 0,-100000000, -100000000,  opponent_symb);

                // Undo the move
                board[i][j] = backup;

                // Update the best value if the move is better
                if (moveVal > bestVal) {
                    *bestRow = i;
                    *bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestVal; // Return the value of the best move
}


char move_hard_bot_4x4(char num[17], char opponent_symb) {
    int bestRow, bestCol;

    // Translate the 1D board array to a 2D board
    translate_to_board_4x4(board, num);

    // Get the best move
    findBestMove_4x4(board, &bestRow, &bestCol, opponent_symb);

    int move = (4 * bestRow) + bestCol + 1;
    return num[move];
}

char move_medium_bot_4x4(char num[17], char opponent_symb){
    translate_to_board_4x4(board, num);
     for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // Check if the current cell is available
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];

                // Make the move
                board[i][j] = opponent_symb;
                int value = evaluate_4x4(board, opponent_symb);
                if(value == -10){
                    int move = (4 * i) + j + 1;
                    return num[move];
                }
                // Undo the move
                board[i][j] = backup;
            }
        }
     }
        char move = bot_move_4x4(num);
        return move;
}
