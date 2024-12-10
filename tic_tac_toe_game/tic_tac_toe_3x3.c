/*******************************************************************************
* Title                 :   Tic Tac Toe board 3x3 game file
* Filename              :   tic_tac_toe_3x3.c
* Author                :   TMF
* Origin Date           :   18/11/2024
* Version               :   1.0.0
* Compiler              :   GNU GCC Compiler
* Target                :   i686-w64-mingw32
* Notes                 :   None
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "easy_bot.h"
#include "hard_bot.h"
#include "player.h"

/*
 Tic Tac Toe 3X3 game
*/

char num[10] = {'o','1','2','3','4','5','6','7','8','9'};

// Function Prototypes
int win();
void game(char *player1, char *player2);
int start_game_3x3(char *player1, char *player2);
int start_game_3x3_bot(int bot_level, char *player1, char *player2);
int clear_num_array();

/*
    Function to return status 1 for game over with a success,
    -1 for game in progress & 0 for game over & draw situation.
*/

int win()
{
    if (num[1] == num[2] && num[2] == num[3])
        return 1;
    else if (num[4] == num[5] && num[5] == num[6])
        return 1;
    else if (num[7] == num[8] && num[8] == num[9])
        return 1;
    else if (num[1] == num[4] && num[4] == num[7])
        return 1;
    else if (num[2] == num[5] && num[5] == num[8])
        return 1;
    else if (num[3] == num[6] && num[6] == num[9])
        return 1;
    else if (num[1] == num[5] && num[5] == num[9])
        return 1;
    else if (num[3] == num[5] && num[5] == num[7])
        return 1;
    else if (num[1] != '1' && num[2] != '2' && num[3] != '3'
             && num[4] != '4' && num[5] != '5' && num[6] != '6'
             && num[7] != '7' && num[8] != '8' && num[9] != '9')
        return 0;
    else
        return -1;
}

void game(char *player1, char *player2) // Function to draw the player's game board along with their input
{
    printf("\033[2J\033[H"); // Clear screen and reset cursor
    printf("\n\n\tTic Tac Toe\n\n");
    printf("%s (X)  -  %s (O)\n\n", player1, player2);
    printf("\n");



    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c\n", num[1], num[2], num[3]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c\n", num[4], num[5], num[6]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c\n", num[7], num[8], num[9]);
    printf("     |     |     \n\n");
}

// run game with two players
int start_game_3x3(char *player1, char *player2)
{
    return start_game_3x3_bot(-1, player1, player2);
}

// run game with bot
int start_game_3x3_bot(int bot_level, char *player1, char *player2)
{
    int player = 1, i, ch;
    char m;
    int winner;

    do
    {
        game(player1, player2);
        player = (player % 2) ? 1 : 2;
        // play with another player
        if(bot_level == -1)
        {

            printf("%s, enter a number: ", (player == 1)? player1: player2);
            scanf("%d", &ch);
        }
        // play with easy bot
        else if(bot_level == 0)
        {
            if (player == 1)
            {
                // Human player input
                printf("Player %d, enter a number: ", player);
                scanf("%d", &ch);
            }
            else
            {
                // Call bot_move to get the bot's move
                ch = bot_move(num);
                printf("Bot (Player %d) chooses: %d\n", player, ch);
            }
        }
        // play with medium bot
        else if(bot_level == 1)
        {
            if (player == 1)
            {
                // Human player input
                printf("Player %d, enter a number: ", player);
                scanf("%d", &ch);
            }
            else
            {
                // Call bot_move to get the bot's move
                ch = move_medium_bot(num, 'X');
                printf("Bot (Player %d) chooses: %d\n", player, ch);
            }
        }
        // play with hard bot
        else if(bot_level == 2)
        {
            if (player == 1)
            {
                // Human player input
                printf("Player %d, enter a number: ", player);
                scanf("%d", &ch);
            }
            else
            {
                // Call bot_move to get the bot's move
                ch = move_hard_bot(num, 'X');
                printf("Bot (Player %d) chooses: %d\n", player, ch);
            }
        }
        m = (player == 1) ? 'X' : 'O';

        if (ch == 1 && num[1] == '1')
            num[1] = m;
        else if (ch == 2 && num[2] == '2')
            num[2] = m;
        else if (ch == 3 && num[3] == '3')
            num[3] = m;
        else if (ch == 4 && num[4] == '4')
            num[4] = m;
        else if (ch == 5 && num[5] == '5')
            num[5] = m;
        else if (ch == 6 && num[6] == '6')
            num[6] = m;
        else if (ch == 7 && num[7] == '7')
            num[7] = m;
        else if (ch == 8 && num[8] == '8')
            num[8] = m;
        else if (ch == 9 && num[9] == '9')
            num[9] = m;
        else
        {
            printf("Invalid move ");
            player--;
            getchar(); // To consume the newline character
        }
        i = win();
        player++;
    }
    while (i == -1);

    game(player1, player2);
    if (i == 1)
    {
        // return game result if two players
        if(bot_level == -1)
        {
            printf("==> %s wins!\n",(--player == 1)? player1: player2);
            // loading list of players
            winner = --player;
        }
        //return if playing with computer
        else{
            winner = (--player==1)? 0: -1;
            printf("==> %s wins!\n",(winner == 0)? player1: "Computer");
        }
    }
    else
    {
        printf("==> Game draw\n");
        winner = -1;
    }

    getchar(); // Wait for user input before exiting
    clear_num_array();
    // return id of winner player o if player 1, 1 - if player 2
    return winner;
}

// clear num array for new game
int clear_num_array()
{
    for( int i =0; i<10; i++)
    {
        num[i] = i + '0';
    }
    return 1;
}
