#include <stdio.h>
#include <conio.h> // For _getch()
#include <windows.h> // For system("cls")
#include "tic_tac_toe_3x3.h"
#include "player.h"

// Define screen states
typedef enum {
    SCREEN_MAIN_MENU,
    SCREEN_PLAY_WITH_OTHER_PLAYER,
    SCREEN_CHOOSE_BOARD,
    SCREEN_TOURNAMENT_SINGLE_GAME,
    SCREEN_PLAY_WITH_COMPUTER,
    SCREEN_PLAYERS_AND_RESULTS,
    SCREEN_PLAY_GAME,
    SCREEN_EXIT,
    SCREEN_CHOOSE_COMPUTER,
    SCREEN_CHOOSE_PLAYER
} ScreenState;

Player players[2] = {
    {0, "Player 1", 9, 1},
    {2, "Player 2", 11, 4},
};


// Function prototypes for screens
void main_menu(ScreenState *current_screen, int *play_with_computer);
//void play_with_other_player(ScreenState *current_screen, int *typeof_board);
void choose_board(ScreenState *current_screen, int *typeof_board);
void tournament_single_game(ScreenState *current_screen, int *tournament_state, int *play_with_computer);
//void play_with_conputer(ScreenState *current_screen);
void players_and_results(ScreenState *current_screen);
void play_game(int *play_with_computer, int *typeof_board, int *tournament_state, int *computer_level);
void choose_computer(ScreenState *current_screen, int *computer_level);
void choose_player(ScreenState *current_screen, int *play_with_computer);

void draw_menu(const char *options[], int num_options, int selected_option);


// processing screen states
int main() {
    ScreenState current_screen = SCREEN_MAIN_MENU;
    int typeof_board = 0; // 0 - 3x3 board, 1 - 4x4
    int tournament_state = 0; // 0 - one game, 1 - tournament
    int play_with_computer = 0; // 0 - play with another player, 1- play with computer
    int computer_level = 0; // 0 - easy, 1 - medium, 2 - hard

    while (current_screen != SCREEN_EXIT) {
        switch (current_screen) {
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
                choose_player(&current_screen, &play_with_computer);
                break;
            case SCREEN_CHOOSE_COMPUTER:
                choose_computer(&current_screen, &computer_level);
                break;
            case SCREEN_PLAY_GAME:
                current_screen = SCREEN_MAIN_MENU;
                play_game( &play_with_computer, &typeof_board, &tournament_state, &computer_level);
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
void draw_menu(const char *options[], int num_options, int selected_option) {
    printf("\033[2J\033[H"); // Clear screen and reset cursor

    printf("\t=== Menu ===\n\n");
    for (int i = 0; i < num_options; i++) {
        if (i == selected_option) {
            printf(" > %s\n", options[i]); // Highlight selected option
        } else {
            printf("   %s\n", options[i]);
        }
    }
}

// Main menu screen
void main_menu(ScreenState *current_screen, int *play_with_computer) {
    const char *options[] = {
    "Play with Another Player",
    "Play with Computer",
    "Players and Results",
    "Exit"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

    while (1) {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224) { // Arrow keys
            ch = _getch();
            switch (ch) {
                case 72: // Up arrow
                    selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                    break;
                case 80: // Down arrow
                    selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                    break;
            }
        } else if (ch == 13) { // Enter key
            switch (selected_option) {
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
void choose_board(ScreenState *current_screen, int *typeof_board) {
    const char *options[] = {
        "3X3",
        "4X4",
        "Return to Main Menu"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

    while (1) {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224) { // Arrow keys
            ch = _getch();
            switch (ch) {
                case 72: // Up arrow
                    selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                    break;
                case 80: // Down arrow
                    selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                    break;
            }
        } else if (ch == 13) { // Enter key
            switch (selected_option) {
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
void tournament_single_game(ScreenState *current_screen, int *tournament_state, int *play_with_computer){
    const char *options[] = {
        "One Game",
        "Tournament",
        "Return to Main Menu"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

  while (1) {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224) { // Arrow keys
            ch = _getch();
            switch (ch) {
                case 72: // Up arrow
                    selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                    break;
                case 80: // Down arrow
                    selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                    break;
            }
        } else if (ch == 13) { // Enter key
            switch (selected_option) {
                // one game
                case 0:
                    *tournament_state = 0;
                    if(*play_with_computer == 1){
                        *current_screen = SCREEN_CHOOSE_COMPUTER;
                    }else{
                    *current_screen = SCREEN_PLAY_GAME;
                    }
                    return;
                // tournament
                case 1:
                    *tournament_state = 1;
                    if(*play_with_computer == 1){
                        *current_screen = SCREEN_CHOOSE_COMPUTER;
                    }else {
                        *current_screen = SCREEN_PLAY_GAME;
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

void choose_computer(ScreenState *current_screen, int *computer_level){
        const char *options[] = {
        "Easy",
        "Medium",
        "Hard",
        "Return to Main Menu"
    };
    int num_options = sizeof(options) / sizeof(options[0]);
    int selected_option = 0;

  while (1) {
        draw_menu(options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224) { // Arrow keys
            ch = _getch();
            switch (ch) {
                case 72: // Up arrow
                    selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                    break;
                case 80: // Down arrow
                    selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                    break;
            }
        } else if (ch == 13) { // Enter key
            switch (selected_option) {
                // Easy
                case 0:
                    *current_screen = SCREEN_PLAY_GAME;
                    *computer_level = 0;
                    return;
                // Medium
                case 1:
                    *current_screen = SCREEN_PLAY_GAME;
                    *computer_level = 1;
                    return;
                // Hard
                case 2:
                    *current_screen = SCREEN_PLAY_GAME;
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


void choose_player(ScreenState *current_screen, int *play_with_computer) {
    int num_options = sizeof(players) / sizeof(players[0]);
    char *options[num_options];
    int selected_option = 0;

    for (int i = 0; i < num_options; i++) {
        options[i] = players[i].name; // Assign player names
    }

    while (1) {
        draw_menu((const char **)options, num_options, selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224) { // Arrow keys
            ch = _getch();
            switch (ch) {
                case 72: // Up arrow
                    selected_option = (selected_option > 0) ? selected_option - 1 : num_options - 1;
                    break;
                case 80: // Down arrow
                    selected_option = (selected_option < num_options - 1) ? selected_option + 1 : 0;
                    break;
            }
        } else if (ch == 13) { // Enter key
            printf("Selected Player: %s\n", players[selected_option].name);
            _getch(); // Wait for input to continue
            *current_screen = SCREEN_MAIN_MENU;
            return;
        }
    }
}


void play_game(int *play_with_computer, int *typeof_board, int *tournament_state, int *computer_level){
   // printf("Play with computer: %d, Type Of Board: %d, Tournament: %d", play_with_computer, typeof_board, tournament_state);
    if(!*play_with_computer){
            start_game_3x3();
            _getch();
            return;
    }else if(*play_with_computer){
        start_game_3x3_bot(0);
        _getch();
        return;
    }

    _getch();
    return;

}


void players_and_results(ScreenState *current_screen){
    return;
}
