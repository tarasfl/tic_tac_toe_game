#ifndef MINIMAX_H
#define MINIMAX_H

extern int size; // Declare SIZE as an external variable
int max(int a, int b);
int min(int a, int b);
void translate_to_one_array(char num[size*size+1], char board[size][size]);
void translate_to_board(char board[size][size], char num[size*size+1]);
int isMovesLeft(char board[size][size]);

#endif
