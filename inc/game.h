#ifndef SCOUNDREL_GAME_H
#define SCOUNDREL_GAME_H

#include "globals.h"

#define GAME_ROOM_CAPACITY 4
#define GAME_WEAPON_CAPACITY 27

typedef struct Deck {
    int capacity;
    int size;
    Card cards[DECK_CAPACITY];
} Deck;

typedef struct Game {
    Deck deck;
    Card room[GAME_ROOM_CAPACITY];
    Card weapon[GAME_WEAPON_CAPACITY];
} Game;

void init_game();
Game* get_game();
Deck* get_deck();

void deck_shuffle();
void room_draw();
void room_run();

#endif