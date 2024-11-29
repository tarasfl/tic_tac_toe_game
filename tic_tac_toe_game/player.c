#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int wins;
    int losses;
} Player;


// write new list of players into file
void savePlayerData(const char *filename, Player *players, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    // writing players line by line from players array
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %d\n", players[i].name, players[i].wins, players[i].losses);
    }

    fclose(file);
    printf("Player data saved successfully.\n");
}

// Function to load player data from a file
int loadPlayerData(const char *filename, Player *players, int maxPlayers) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return 0;
    }
    // reading players line by line and writing data into array
    int count = 0;
    while (fscanf(file, "%s %d %d", players[count].name, &players[count].wins, &players[count].losses) == 3) {
        count++;
        if (count >= maxPlayers) break;
    }

    fclose(file);
    printf("Player data loaded successfully.\n");
    return count;
}


// Function to update a player's stats
void updatePlayerStats(Player *players, int *count, const char *name, int wins, int losses) {
    int index = findPlayerByName(players, *count, name);

    if (index == -1) {  // Player not found, add new player
        strcpy(players[*count].name, name);
        players[*count].wins = wins;
        players[*count].losses = losses;
        (*count)++;
        printf("New player '%s' added.\n", name);
    } else {  // Player found, update stats
        players[index].wins += wins;
        players[index].losses += losses;
        printf("Player '%s' stats updated.\n", name);
    }
}


// Function to find a player by name for checking whether name is taken
int findPlayerByName(Player *players, int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return i; // number of line where player is located
        }
    }
    return -1;  // Not found
}

// function for exclude chosen player
int excludePlayerByName(Player players[], int count, const char *excludeName, Player result[]) {
    int newCount = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, excludeName) != 0) {  // Compare names
            result[newCount++] = players[i];  // Copy player to the result array
        }
    }
    return newCount;  // Return the new size of the result array
}

