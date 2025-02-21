#include "game.h"

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
}

Game* get_game() {
    return &game;
}

Deck* get_deck() {
    return &game.deck;
}