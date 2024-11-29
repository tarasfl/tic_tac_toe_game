#ifndef PLAYER_H
#define PLAYER_H

// Define your struct here
typedef struct {
    int id;
    char name[50];
    int wins;
    int losses;
} Player;
void savePlayerData(const char *filename, Player *players, int count);
int loadPlayerData(const char *filename, Player *players, int maxPlayers);
void updatePlayerStats(Player *players, int *count, const char *name, int wins, int losses);
int findPlayerByName(Player *players, int count, const char *name);
int excludePlayerByName(Player players[], int count, const char *excludeName, Player result[]);
#endif
