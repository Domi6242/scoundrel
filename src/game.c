#include "game.h"
#include "raylib.h"

Game game;

void init_deck() {
    game.deck.capacity = DECK_CAPACITY;
    game.deck.size = DECK_CAPACITY;
    int j = CARD_2_OF_HEARTS;
    for (int i = 0; i < DECK_CAPACITY; i++) {
        while (i + j == CARD_ACE_OF_HEARTS || i + j == CARD_ACE_OF_DIAMONDS || i + j == CARD_KING_OF_HEARTS ||
               i + j == CARD_KING_OF_DIAMONDS || i + j == CARD_QUEEN_OF_HEARTS || i + j == CARD_QUEEN_OF_DIAMONDS ||
               i + j == CARD_JACK_OF_HEARTS || i + j == CARD_JACK_OF_DIAMONDS) {
            j++;
        }
        game.deck.cards[i] = i + j;
    }
}

void init_game() {
    init_deck();
    for (int i = 0; i < GAME_ROOM_CAPACITY; i++) { game.room[i] = CARD_BLANK; }
    for (int i = 0; i < GAME_WEAPON_CAPACITY; i++) { game.weapon[i] = CARD_BLANK; }
    deck_shuffle();
}

Game* get_game() {
    return &game;
}

Deck* get_deck() {
    return &game.deck;
}

void deck_shuffle() {
    for (int i = game.deck.size - 1; i > 0; i--) {
        int j = GetRandomValue(0, i);
        Card t = game.deck.cards[j];
        game.deck.cards[j] = game.deck.cards[i];
        game.deck.cards[i] = t;
    }
}

void room_draw() {
    for (int i = 0; i < GAME_ROOM_CAPACITY; i++) {
        if (get_deck()->size == 0) { break; }
        if (get_game()->room[i] != CARD_BLANK) { continue; }

        // draw a card
        get_game()->room[i] = get_deck()->cards[get_deck()->size - 1];
        get_deck()->cards[get_deck()->size - 1] = CARD_BLANK;
        get_deck()->size--;
    }
}

void room_run() {
    // get room size
    int room_size = 0;
    while (get_game()->room[room_size] != CARD_BLANK) { room_size++; }

    if (room_size == 0) { return; }

    // shuffle room
    for (int i = room_size - 1; i > 0; i--) {
        int j = GetRandomValue(0, i);
        Card t = get_game()->room[j];
        get_game()->room[j] = get_game()->room[i];
        get_game()->room[i] = t;
    }

    // make room in the deck
    for (int i = get_deck()->size - 1; i >= 0; i--) {
        get_deck()->cards[i + room_size] = get_deck()->cards[i];
    }

    get_deck()->size += room_size;

    // move cards
    for (int i = 0; i < room_size; i++) {
        get_deck()->cards[i] = get_game()->room[i];
        get_game()->room[i] = CARD_BLANK;
    }
}