#include <stdio.h>
#include <stdlib.h>

/*
 Tic Tac Toe 3X3 game
*/

char num_4x4[17] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};


/*
    Function to return status 1 for game over with a success,
    -1 for game in progress & 0 for game over & draw situation.
*/

int win_4x4()
{
    if (num_4x4[1] == num_4x4[2] && num_4x4[2] == num_4x4[3] && num_4x4[3] == num_4x4[4])
        return 1;
    else if (num_4x4[5] == num_4x4[6] && num_4x4[6] == num_4x4[7] && num_4x4[7] == num_4x4[8])
        return 1;
    else if (num_4x4[9] == num_4x4[10] && num_4x4[10] == num_4x4[11] && num_4x4[11] == num_4x4 [12])
        return 1;
    else if (num_4x4[13] == num_4x4[14] && num_4x4[14] == num_4x4[15] && num_4x4[15] == num_4x4[16])
        return 1;
    else if (num_4x4[1] == num_4x4[5] && num_4x4[5] == num_4x4[9] && num_4x4[9] == num_4x4[13])
        return 1;
    else if (num_4x4[2] == num_4x4[6] && num_4x4[6] == num_4x4[10] && num_4x4[10] == num_4x4[14])
        return 1;
    else if (num_4x4[3] == num_4x4[7] && num_4x4[7] == num_4x4[11] && num_4x4[11] == num_4x4[15])
        return 1;
    else if (num_4x4[4] == num_4x4[8] && num_4x4[8] == num_4x4[12] && num_4x4[12] == num_4x4[16])
        return 1;
    else if (num_4x4[1] == num_4x4[6] && num_4x4[6] == num_4x4[11] && num_4x4[11] == num_4x4[16])
        return 1;
    else if (num_4x4[4] == num_4x4[7] && num_4x4[7] == num_4x4[10] && num_4x4[10] == num_4x4[13])
        return 1;
    else if (num_4x4[1] != '1' && num_4x4[2] != '2' && num_4x4[3] != '3'
             && num_4x4[4] != '4' && num_4x4[5] != '5' && num_4x4[6] != '6'
             && num_4x4[7] != '7' && num_4x4[8] != '8' && num_4x4[9] != '9'
             && num_4x4[10] != 'A' && num_4x4[11] != 'B' && num_4x4[12] != 'C'
             && num_4x4[13] != 'D' && num_4x4[14] != 'E' && num_4x4[15] != 'F' && num_4x4[16] != 'G')
        return 0;
    else
        return -1;
}

void game_4x4(char *player1, char *player2) // Function to draw the player's game board along with their input
{
    printf("\033[2J\033[H"); // Clear screen and reset cursor
    printf("\n\n\tTic Tac Toe\n\n");
    printf("Player 1 (X)  -  Player 2 (O)\n\n");
    printf("\n");



    printf("     |     |     |     \n");
    printf("  %c  |  %c  |  %c  |  %c\n", num_4x4[1], num_4x4[2], num_4x4[3], num_4x4[4]);
    printf("_____|_____|_____|______\n");
    printf("     |     |     |     \n");
    printf("  %c  |  %c  |  %c  |  %c\n", num_4x4[5], num_4x4[6], num_4x4[7], num_4x4[8]);
    printf("_____|_____|_____|______\n");
    printf("     |     |     |     \n");
    printf("  %c  |  %c  |  %c  |  %c\n", num_4x4[9], num_4x4[10], num_4x4[11], num_4x4[12]);
    printf("_____|_____|_____|______\n");
    printf("     |     |     |     \n");
    printf("  %c  |  %c  |  %c  |  %c\n", num_4x4[13], num_4x4[14], num_4x4[15], num_4x4[16]);
    printf("     |     |     |     \n");
}

// run game with two players
int start_game_4x4(char *player1, char *player2){
    return start_game_4x4_bot(-1, player1, player2);
}

// run game with bot
int start_game_4x4_bot(int bot_level, char *player1, char *player2)
{
    int player = 1, i, winner;
    char m, ch;
    char input_buffer[10];  // For handling the input as a string
    do
    {
        game_4x4(player1, player2);
        player = (player % 2) ? 1 : 2;
        if(bot_level == -1){

            printf("%s, enter a number: ", (player == 1)? player1: player2);
             // Read a single character
            fgets(input_buffer, sizeof(input_buffer), stdin);  // Use fgets to avoid leftover '\n' from previous inputs

            // Convert input to integer (if valid)
            ch = input_buffer[0];  // Convert char to int (e.g., '1' -> 1);
        }else if(bot_level == 0){
            if (player == 1) {
                // Human player input
                printf("Player %d, enter a number: ", player);
                scanf("%d", &ch);

            } else {
                // Call bot_move to get the bot's move
                printf("Bot (Player %d) chooses: %d\n", player, ch);
            }
        }else if(bot_level == 2){
            if (player == 1) {
                // Human player input
                printf("Player %d, enter a number: ", player);
                scanf("%d", &ch);
            } else {
                // Call bot_move to get the bot's move
                printf("Bot (Player %d) chooses: %d\n", player, ch);
            }
        }
        m = (player == 1) ? 'X' : 'O';

        if (ch == '1' && num_4x4[1] == '1')
            num_4x4[1] = m;
        else if (ch == '2' && num_4x4[2] == '2')
            num_4x4[2] = m;
        else if (ch == '3' && num_4x4[3] == '3')
            num_4x4[3] = m;
        else if (ch == '4' && num_4x4[4] == '4')
            num_4x4[4] = m;
        else if (ch == '5' && num_4x4[5] == '5')
            num_4x4[5] = m;
        else if (ch == '6' && num_4x4[6] == '6')
            num_4x4[6] = m;
        else if (ch == '7' && num_4x4[7] == '7')
            num_4x4[7] = m;
        else if (ch == '8' && num_4x4[8] == '8')
            num_4x4[8] = m;
        else if (ch == '9' && num_4x4[9] == '9')
            num_4x4[9] = m;
        else if ((ch == 'a' || ch == 'A') && num_4x4[10] == 'A' || ch == 10 && num_4x4[10] == 'a')
            num_4x4[10] = m;
        else if ((ch == 'b' || ch == 'B') && num_4x4[11] == 'B')
            num_4x4[11] = m;
        else if ((ch == 'c' || ch == 'C') && num_4x4[12] == 'C')
            num_4x4[12] = m;
        else if ((ch == 'd' || ch == 'D') && num_4x4[13] == 'D')
            num_4x4[13] = m;
        else if ((ch == 'e' || ch == 'E') && num_4x4[14] == 'E')
            num_4x4[14] = m;
        else if ((ch == 'f' || ch == 'F') && num_4x4[15] == 'F')
            num_4x4[15] = m;
        else if ((ch == 'g' || ch == 'G') && num_4x4[16] == 'G')
            num_4x4[16] = m;
        else
        {
            printf("Invalid move ");
            player--;
            getchar(); // To consume the newline character
        }
        i = win_4x4();
        player++;
    }
    while (i == -1);

    game_4x4(player1, player2);
    if (i == 1){
        printf("==> %s wins!\n",(--player == 1)? player1: player2);
        winner = --player;
    }
    else{
        printf("==> Game draw\n");
        winner == -1;
    }

    getchar(); // Wait for user input before exiting
    clear_num_array_4x4();

    return winner;
}

int clear_num_array_4x4(){
    for( int i =0; i<17; i++){
        num_4x4[i] = i + '0';
    }
    return 1;
}