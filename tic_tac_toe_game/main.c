#include <stdio.h>
#include <conio.h> // For _getch()
#include <windows.h> // For system("cls")
#include "tic_tac_toe_3x3.h"
#include "player.h"
#include "tic_tac_toe_4x4.h"

// Define screen states
typedef enum
{
    SCREEN_MAIN_MENU,
    SCREEN_PLAY_WITH_OTHER_PLAYER,
    SCREEN_CHOOSE_BOARD,
    SCREEN_TOURNAMENT_SINGLE_GAME,
    SCREEN_PLAY_WITH_COMPUTER,
    SCREEN_PLAYERS_AND_RESULTS,
    SCREEN_PLAY_GAME,
    SCREEN_EXIT,
    SCREEN_CHOOSE_COMPUTER,
    SCREEN_CHOOSE_PLAYER,
    SCREEN_CREATE_NEW_PLAYER
} ScreenState;


// Function prototypes for screens
void main_menu(ScreenState *current_screen, int *play_with_computer);
void choose_board(ScreenState *current_screen, int *typeof_board);
void tournament_single_game(ScreenState *current_screen, int *tournament_state, int *play_with_computer);
void players_and_results(ScreenState *current_screen, Player players[], int *playCount);
void create_new_player(ScreenState *current_screen, Player players[], int *playerCount);
void play_game(int *play_with_computer, int *typeof_board, int *tournament_state, int *computer_level, Player players[],  int *playerCount, char *player1, char *player2);
void choose_computer(ScreenState *current_screen, int *computer_level);
void choose_player(ScreenState *current_screen, int *play_with_computer, Player players[], char *player1, char *player2);

void draw_menu(const char *options[], int num_options, int selected_option);


// processing screen states
int main()
{
    ScreenState current_screen = SCREEN_MAIN_MENU;
    int typeof_board = 0; // 0 - 3x3 board, 1 - 4x4
    int tournament_state = 0; // 0 - one game, 1 - tournament
    int play_with_computer = 0; // 0 - play with another player, 1- play with computer
    int computer_level = 0; // 0 - easy, 1 - medium, 2 - hard
    Player players[100];  // Array to store players
    int playerCount = 0; // number of players
    char player1[50]; // name for player 1
    char player2[50]; // name for player 2

    while (current_screen != SCREEN_EXIT)
    {
        switch (current_screen)
        {
        case SCREEN_MAIN_MENU:
            main_menu(&current_screen, &play_with_computer);
            break;
        case SCREEN_CHOOSE_BOARD:
            choose_board(&current_screen, &typeof_board);
            break;
        case SCREEN_TOURNAMENT_SINGLE_GAME:
            tournament_single_game(&current_screen, &tournament_state, &play_with_computer);
            break;
        case SCREEN_PLAYERS_AND_RESULTS:
            players_and_results(&current_screen, players, &playerCount);
            break;
        case SCREEN_CREATE_NEW_PLAYER:
            create_new_player(&current_screen, players, &playerCount);
            break;
        case SCREEN_CHOOSE_COMPUTER:
            choose_computer(&current_screen, &computer_level);
            break;
        case SCREEN_PLAY_GAME:
            current_screen = SCREEN_MAIN_MENU;
            play_game( &play_with_computer, &typeof_board, &tournament_state, &computer_level, players, &playerCount, player1, player2);
            break;
        case SCREEN_CHOOSE_PLAYER:
            choose_player(&current_screen, &play_with_computer, players, &player1, &player2);
            break;
        default:
            printf("Unknown screen. Exiting...\n");
            current_screen = SCREEN_MAIN_MENU;
            break;
        }
    }

    printf("Exiting program. Goodbye!\n");
    return 0;
}

// Draws a menu with options and highlights the selected option


void draw_menu(const char *options[], int num_options, int selected_option)
{
    //printf("\033[2J\033[H"); // Clear screen and reset cursor
    system("cls");
    printf("\t=== Menu ===\n\n");
    for (int i = 0; i < num_options; i++)
    {
        if (i == selected_option)
        {
            printf(" > %s\n", options[i]); // Highlight selected option
        }
        else
        {
            printf("   %s\n", options[i]);
        }
    }
}

// Main menu screen
void main_menu(ScreenState *current_screen, int *play_with_computer)
{
    const char *options[] =
    {
        "Play with Another Player",
        "Play with Computer",
        "Players and Results",
        "Exit"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

    while (1)
    {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224)   // Arrow keys
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // Up arrow
                selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                break;
            case 80: // Down arrow
                selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                break;
            }
        }
        else if (ch == 13)     // Enter key
        {
            switch (selected_option)
            {
            case 0:
                *current_screen = SCREEN_CHOOSE_BOARD;
                *play_with_computer = 0;
                return;
            case 1:
                *current_screen = SCREEN_CHOOSE_BOARD;
                *play_with_computer = 1;
                return;
            case 2:
                *current_screen = SCREEN_PLAYERS_AND_RESULTS;
                return;
            case 3:
                *current_screen = SCREEN_EXIT;
                return;
            }
        }
    }
}

// play with another player screen
void choose_board(ScreenState *current_screen, int *typeof_board)
{
    const char *options[] =
    {
        "3X3",
        "4X4",
        "Return to Main Menu"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

    while (1)
    {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224)   // Arrow keys
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // Up arrow
                selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                break;
            case 80: // Down arrow
                selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                break;
            }
        }
        else if (ch == 13)     // Enter key
        {
            switch (selected_option)
            {
            case 0:
                *current_screen = SCREEN_TOURNAMENT_SINGLE_GAME;
                *typeof_board = 0;
                return;
            case 1:
                *current_screen = SCREEN_TOURNAMENT_SINGLE_GAME;
                *typeof_board = 1;
                return;
            case 2:
                *current_screen = SCREEN_MAIN_MENU;
                return;
            }
        }
    }
}

// choosing one game or tournament
void tournament_single_game(ScreenState *current_screen, int *tournament_state, int *play_with_computer)
{
    const char *options[] =
    {
        "One Game",
        "Tournament",
        "Return to Main Menu"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

    while (1)
    {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224)   // Arrow keys
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // Up arrow
                selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                break;
            case 80: // Down arrow
                selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                break;
            }
        }
        else if (ch == 13)     // Enter key
        {
            switch (selected_option)
            {
            // one game
            case 0:
                *tournament_state = 0;
                if(*play_with_computer == 1)
                {
                    *current_screen = SCREEN_CHOOSE_COMPUTER;
                }
                else
                {
                    *current_screen = SCREEN_CHOOSE_PLAYER;
                }
                return;
            // tournament
            case 1:
                printf("Enter number of games in tournament: ");
                scanf(" %d", tournament_state);
                if(*play_with_computer == 1)
                {
                    *current_screen = SCREEN_CHOOSE_COMPUTER;
                }
                else
                {
                    *current_screen = SCREEN_CHOOSE_PLAYER;
                }
                return;
            // exit
            case 2:
                *current_screen = SCREEN_MAIN_MENU;
                return;
            }
        }
    }
}

void choose_computer(ScreenState *current_screen, int *computer_level)
{
    const char *options[] =
    {
        "Easy",
        "Medium",
        "Hard",
        "Return to Main Menu"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

    while (1)
    {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224)   // Arrow keys
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // Up arrow
                selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                break;
            case 80: // Down arrow
                selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                break;
            }
        }
        else if (ch == 13)     // Enter key
        {
            switch (selected_option)
            {
            // Easy
            case 0:
                *current_screen = SCREEN_CHOOSE_PLAYER;
                *computer_level = 0;
                return;
            // Medium
            case 1:
                *current_screen = SCREEN_CHOOSE_PLAYER;
                *computer_level = 1;
                return;
            // Hard
            case 2:
                *current_screen = SCREEN_CHOOSE_PLAYER;
                *computer_level = 2;
                return;
            // exit
            case 3:
                *current_screen = SCREEN_MAIN_MENU;
                return;
            }
        }
    }
}

// choosing player to play
void choose_player(ScreenState *current_screen, int *play_with_computer, Player players[], char *player1, char *player2)
{
    // Load player data
    int playerCount = loadPlayerData("players.txt", players, 100);

    char *options[playerCount];
    int selected_option = 0;

    // Populate options with player names
    for (int i = 0; i < playerCount; i++)
    {
        options[i] = players[i].name;
    }

    while (1)
    {
        // Display the menu and the selected players
        draw_menu((const char **)options, playerCount, selected_option);
        int ch = _getch();
        if (ch == 0 || ch == 224)   // Arrow keys
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // Up arrow
                selected_option = (selected_option > 0) ? selected_option - 1 : playerCount - 1;
                break;
            case 80: // Down arrow
                selected_option = (selected_option < playerCount - 1) ? selected_option + 1 : 0;
                break;
            }
        }
        else if (ch == 13)     // Enter key
        {
            if (findPlayerByName(players, playerCount, player1) == -1)
            {
                // Assign to player1 if not selected
                strcpy(player1, players[selected_option].name);
            }

            else if (findPlayerByName(players, playerCount, player2) == -1 && strcmp(player1, players[selected_option].name) != 0)
            {
                // Assign to player2 if not selected and not the same as player1
                strcpy(player2, players[selected_option].name);
            }
            else if(strcmp(player1, players[selected_option].name) == 0)
            {
                // print warning message if player is taken
                printf("%s is taken choose another player", player1);
                _getch();
            }

            // Handle screen transition logic
            if (*play_with_computer)
            {
                strcpy(player2, "Computer");
                // Single-player: Only player1 is needed
                if (player1[0] != '\0')
                {
                    *current_screen = SCREEN_PLAY_GAME;
                    return;
                }
            }
            else
            {
                // Multiplayer: Both player1 and player2 are needed
                if (findPlayerByName(players, playerCount, player1) != -1 && findPlayerByName(players, playerCount, player2) != -1)
                {
                    *current_screen = SCREEN_PLAY_GAME;
                    return;
                }
            }
        }
    }
}






void play_game(int *play_with_computer, int *typeof_board, int *tournament_state, int *computer_level,  Player players[],  int *playerCount, char *player1, char *player2)
{
    if(*tournament_state == 0)
    {
        if(!*play_with_computer)
        {
            // var for returning winner
            int winner;
            if(!*typeof_board)
                winner = start_game_3x3(player1, player2);
            else if(*typeof_board)
                winner = start_game_4x4(player1, player2);
            _getch();
            // write down data for players
            if(winner == 0 || winner == 1)
            {
                players[(winner == 0) ? findPlayerByName(players, playerCount, player1) :  findPlayerByName(players, playerCount, player2)].wins++;
                players[(winner == 0) ? findPlayerByName(players, playerCount, player2) :  findPlayerByName(players, playerCount, player1)].losses++;
                savePlayerData("players.txt", players, *playerCount);
            }
            else
            {
                printf("Game resulted in a draw.\n");
            }
        }
        else if(*play_with_computer)
        {
            int winner;
            if(!*typeof_board)
                winner = start_game_3x3_bot(*computer_level, player1, player2);
            else if(*typeof_board)
                winner = start_game_4x4_bot(*computer_level, player1, player2);
            if(winner == 0)
            {
                players[findPlayerByName(players, playerCount, player1)].wins++;
                savePlayerData("players.txt", players, *playerCount);
            }

        }
        player1[0] = '\0'; // Initialize player1 as empty
        player2[0] = '\0'; // Initialize player2 as empty
    }
    else
    {
        if(!*play_with_computer)
        {
            int winner = -1; // Initialize to -1 for the first game
            for (int i = 0; i < *tournament_state; i++)
            {
                // Play the game with the current player order
                if(!*typeof_board)
                    winner = start_game_3x3(player1, player2);
                else if(*typeof_board)
                    winner = start_game_4x4(player1, player2);
                _getch();

                // Update player statistics only if there's a valid winner
                if (winner == 0 || winner == 1)
                {

                    players[(winner == 0) ? findPlayerByName(players, playerCount, player1) :  findPlayerByName(players, playerCount, player2)].wins++;
                    players[(winner == 0) ? findPlayerByName(players, playerCount, player2) :  findPlayerByName(players, playerCount, player1)].losses++;
                    savePlayerData("players.txt", players, *playerCount);
                }
                else
                {
                    printf("Game resulted in a draw.\n");
                }

                // Swap players if player2 wins
                if (winner == 1)
                {
                    char temp[50]; // Assuming max player name length is 50
                    strcpy(temp, player1);
                    strcpy(player1, player2);
                    strcpy(player2, temp);
                }
            }
        }
        else
        {
            int winner = -1; // Initialize to -1 for the first game
            for (int i = 0; i < *tournament_state; i++)
            {
                // Play the game with the current player order
                if(!*typeof_board)
                    winner = start_game_3x3_bot(*computer_level, player1, player2);
                else if(*typeof_board)
                    winner = start_game_4x4_bot(*computer_level, player1, player2);
                // wait for user input before starting new game
                _getch();
                // Update player statistics only if there's a valid winner
                if(winner == 0)
                {
                    players[findPlayerByName(players, playerCount, player1)].wins++;
                    savePlayerData("players.txt", players, *playerCount);
                }
                else
                {
                    printf("Game resulted in a draw.\n");
                }
            }

        }
        player1[0] = '\0'; // Initialize player1 as empty
        player2[0] = '\0'; // Initialize player2 as empty
    }


    _getch();
    return;

}

// screen to display players and their win lose result
void players_and_results(ScreenState *current_screen, Player players[], int *playerCount)
{
    const char *options[] =
    {
        "Create new Player",
        "Return to Main Menu"
    };
    *playerCount = loadPlayerData("players.txt", players, 100);
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

    while (1)
    {
        draw_menu(options, num_options, selected_option);
        printf("\n\n");
        if(*playerCount > 0)
        {
            printf("\tPlayers:\n");
            for(int i = 0; i < *playerCount; i++)
            {
                printf("\t%s, Wins: %d, Losses: %d\n", players[i].name, players[i].wins, players[i].losses);
            }
        }
        else
            printf("\tNo players founded!\n");

        int ch = _getch();
        if (ch == 0 || ch == 224)   // Arrow keys
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // Up arrow
                selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                break;
            case 80: // Down arrow
                selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                break;
            }
        }
        else if (ch == 13)     // Enter key
        {
            switch (selected_option)
            {
            case 0:
                *current_screen = SCREEN_CREATE_NEW_PLAYER;
                return;;
            case 1:
                *current_screen = SCREEN_MAIN_MENU;
                return;
            }
        }
    }
    _getch();
    *current_screen = SCREEN_MAIN_MENU;
    return;
}

void create_new_player(ScreenState *current_screen, Player players[], int *playerCount)
{
    char name[50];  // Define a fixed size for the name
    printf("Enter a name for the new player: \n");
    scanf("%s", name);  // No need to use & for name, it's already a pointer

    int name_res = findPlayerByName(players, *playerCount, name);  // Assuming findPlayerByName is correct

    // If the name is already taken, ask for a new name
    while (name_res != -1)
    {
        printf("Name is already taken. Please enter a unique name: ");
        scanf("%s", name);  // Again, no need for & here
        name_res = findPlayerByName(players, *playerCount, name);
    }

    // Create and initialize the new player
    Player newPlayer;
    strncpy(newPlayer.name, name, sizeof(newPlayer.name) - 1);  // Safely copy the name
    newPlayer.name[sizeof(newPlayer.name) - 1] = '\0';  // Ensure null termination
    newPlayer.wins = 0;
    newPlayer.losses = 0;

    // Add the new player to the players array
    players[*playerCount] = newPlayer;
    (*playerCount)++;  // Increase player count
    savePlayerData("players.txt", players, *playerCount);
    printf("Player '%s' created successfully!\n", newPlayer.name);
    _getch();
    *current_screen = SCREEN_PLAYERS_AND_RESULTS;
}
