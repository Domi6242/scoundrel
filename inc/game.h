#ifndef SCOUNDREL_GAME_H
#define SCOUNDREL_GAME_H

#include "globals.h"

typedef struct Deck {
    int capacity;
    int size;
    Card cards[DECK_CAPACITY];
} Deck;

typedef struct Game {
    Deck deck;
    Card room[4];
    Card weapon[27];
} Game;

void init_game();
Game* get_game();
Deck* get_deck();

#endif