#include <stdio.h>

#define size 3

char board[size][size];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void translate_to_board(char board[size][size], char num[10]) {
    for (int i = 1; i < (size * size) + 1; i++) {
        int row = (i - 1) / size;
        int column = (i - 1) % size;
        board[row][column] = num[i];
    }
}

void translate_to_one_array(char num[10], char board[size][size]){
     for (int i = 1; i < (size * size) + 1; i++) {
        int row = (i - 1) / size;
        int column = (i - 1) % size;
        num[i] = board[row][column];
    }

}

int isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 1;
            }
        }
    }
    return 0;
}

// Function to evaluate the board
int evaluate(char board[3][3], char opponent_symb) {
    char comp_symb = (opponent_symb=='X') ? 'O': 'X';
    // Check rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == comp_symb) {
                return 10;
            } else if (board[row][0] == opponent_symb) {
                return -10;
            }
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == comp_symb) {
                return 10;
            } else if (board[0][col] == opponent_symb) {
                return -10;
            }
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == comp_symb) {
            return 10;
        } else if (board[0][0] == opponent_symb) {
            return -10;
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == comp_symb) {
            return 10;
        } else if (board[0][2] == opponent_symb) {
            return -10;
        }
    }

    return 0; // No winner
}

// Minimax function
int minimax(char board[3][3], int depth, int isMax, char opponent_symb) {
    int score = evaluate(board, opponent_symb);

    // If the computer has won
    if (score == 10)
        return score - depth; // Depth penalizes longer paths to victory

    // If the opponent has won
    if (score == -10)
        return score + depth; // Depth penalizes longer paths to defeat

    // If no moves are left, it's a draw
    if (!isMovesLeft(board))
        return 0;

    // Depth limit to prevent stack overflow
    if (depth > 10)
        return 0;

    char comp_symb = (opponent_symb == 'X') ? 'O' : 'X';

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = comp_symb;
                    best = max(best, minimax(board, depth + 1, !isMax, opponent_symb));
                    board[i][j] = backup; // Undo move
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = opponent_symb;
                    best = min(best, minimax(board, depth + 1, !isMax, opponent_symb));
                    board[i][j] = backup; // Undo move
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the player
int findBestMove(char board[3][3], int* bestRow, int* bestCol, char opponent_symb) {
    int bestVal = -1000; // Initialize the best value
    int id = -1;
    char comp_symb = (opponent_symb == 'X') ? 'O' : 'X';
    *bestRow = -1;
    *bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Check if the current cell is available
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                // Backup the original value
                char backup = board[i][j];

                // Make the move
                board[i][j] = comp_symb;

                // Evaluate the move
                int moveVal = minimax(board, 0, 0, opponent_symb);

                // Undo the move
                board[i][j] = backup;

                // Update the best value if the move is better
                if (moveVal > bestVal) {
                    *bestRow = i;
                    *bestCol = j;
                    id = (3 * i) + j + 1; // Convert to 1D index
                    bestVal = moveVal;
                }
            }
        }
    }

    return id; // Return the best move index
}

int move_hard_bot(char num[10], char opponent_symb) {
    int bestRow, bestCol;

    // Translate the 1D board array to a 2D board
    translate_to_board(board, num);

    // Get the best move
    int move = findBestMove(board, &bestRow, &bestCol, opponent_symb);

    // Translate back to 1D
    translate_to_one_array(num, board);

    return move;
}



