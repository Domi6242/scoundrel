#ifndef SCOUNDREL_GAME_H
#define SCOUNDREL_GAME_H

#include "globals.h"
#include "raylib.h"

#define GAME_ROOM_CAPACITY 4
#define GAME_ROOM_CARD_PADDING 10
#define GAME_WEAPON_CAPACITY 27

static const Vector2 room_pos = { CARD_W, 5 * CARD_H };

typedef struct Deck {
    int capacity;
    int size;
    Card cards[DECK_CAPACITY];
} Deck;

typedef struct Room {
    int size;
    Card cards[GAME_ROOM_CAPACITY];
    Rectangle card_rects[GAME_ROOM_CAPACITY];
} Room;

typedef struct Game {
    Deck deck;
    Room room;
    Card weapon[GAME_WEAPON_CAPACITY];

    Rectangle clickables[CLICK_COUNT];
} Game;

const Game* get_game();
const Deck* get_deck();
const Room* get_room();

void init_game();

void deck_shuffle();
void room_draw();
void room_run();

void game_logic();

#endif