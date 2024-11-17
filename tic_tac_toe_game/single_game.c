#include <stdio.h>
#include <stdlib.h>
#include "tic_tac_toe_3x3.h"

#define GAME_NUM 2

const char *game_options[GAME_NUM] = {
    "3X3",
    "4X4"
};

static void draw_menu(int selected_option) {
    system("cls"); // Clear the screen

    printf("\t\t\t  === Tic Tac Toe ===\n\n\n\n");
    for (int i = 0; i < GAME_NUM; i++) {
        if (i == selected_option) {
            printf("\t\t\t> %s\n\n\n", game_options[i]); // Highlight selected option
        } else {
            printf("\t\t\t  %s\n\n\n", game_options[i]);
        }
    }
}

int select_game() {
    int selected_option = 0;

    while (1) {
        draw_menu(selected_option);

        int ch = _getch();
        if (ch == 0 || ch == 224) { // Arrow keys
            ch = _getch();
            switch (ch) {
                case 72: // Up arrow
                    selected_option = (selected_option > 0) ? selected_option - 1 : GAME_NUM - 1;
                    break;
                case 80: // Down arrow
                    selected_option = (selected_option < GAME_NUM - 1) ? selected_option + 1 : 0;
                    break;
            }
        } else if (ch == 13) { // Enter key
            switch (selected_option) {
                case 0:
                    printf("\nStarting game...\n");
                    if (!start_single_game(0)) {
                        printf("Something went wrong\n");
                        printf("Quitting...\n");
                        return 1; // Exit with error code
                    }
                    break; // Exit the case after running the game
                case 1:
                    printf("\nStarting game...\n");
                    if (!start_single_game(1)) {
                        printf("Something went wrong\n");
                        printf("Quitting...\n");
                        return 1; // Exit with error code
                    }
                    break; // Exit the case after running the game
            }
        }
    }
    return 0;
}


 int start_single_game(int type){
    if(type == 0){
        // start 3x3 game
        start_game_3x3();
        return 1;
    }else if(type == 1){
        //start 4x4 game
        printf("Here will be game 4x4");
        return 1;
    };
    return 0;
}

