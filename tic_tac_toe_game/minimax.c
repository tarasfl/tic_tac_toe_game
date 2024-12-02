#include <stdio.h>

extern int size; // Declare SIZE as an external variable

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

void translate_to_board(char board[size][size], char num[size*size+1]) {
    for (int i = 1; i < (size * size) + 1; i++) {
        int row = (i - 1) / size;
        int column = (i - 1) % size;
        board[row][column] = num[i];
    }
}

void translate_to_one_array(char num[size*size+1], char board[size][size]){
     for (int i = 1; i < (size * size) + 1; i++) {
        int row = (i - 1) / size;
        int column = (i - 1) % size;
        num[i] = board[row][column];
    }

}

int isMovesLeft(char board[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 1;
            }
        }
    }
    return 0;
}
