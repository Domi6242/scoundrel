#include "game.h"

Game game;

const Game* get_game() {
    return &game;
}

const Deck* get_deck() {
    return &game.deck;
}

const Room* get_room() {
    return &game.room;
}

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

void init_room() {
    game.room.size = 0;
    for (int i = 0; i < GAME_ROOM_CAPACITY; i++) { 
        game.room.cards[i] = CARD_BLANK; 
        game.room.card_rects[i] = (Rectangle) {
            room_pos.x + i * (CARD_W + GAME_ROOM_CARD_PADDING),
            room_pos.y,
            CARD_W,
            CARD_H
        };
    }
}

void init_ui() {
    // Register clickables
    game.clickables[CLICK_ROOM_1] = game.room.card_rects[0];
    game.clickables[CLICK_ROOM_2] = game.room.card_rects[1];
    game.clickables[CLICK_ROOM_3] = game.room.card_rects[2];
    game.clickables[CLICK_ROOM_4] = game.room.card_rects[3];
    game.clickables[CLICK_NONE] = (Rectangle) { -10, -10, 0, 0 };
}

void init_game() {
    init_deck();
    init_room();
    for (int i = 0; i < GAME_WEAPON_CAPACITY; i++) { game.weapon[i] = CARD_BLANK; }

    init_ui();
    deck_shuffle();
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
    if (game.room.size == GAME_ROOM_CAPACITY) { return; }
    for (int i = 0; i < GAME_ROOM_CAPACITY; i++) {
        if (game.deck.size == 0) { break; }
        if (game.room.cards[i] != CARD_BLANK) { continue; }

        // draw a card
        game.room.cards[i] = game.deck.cards[game.deck.size - 1];
        game.room.size++;
        game.deck.cards[game.deck.size - 1] = CARD_BLANK;
        game.deck.size--;
    }
}

void room_run() {
    if (game.room.size == 0) { return; }

    // shuffle room
    for (int i = GAME_ROOM_CAPACITY - 1; i > 0; i--) {
        int j = GetRandomValue(0, i);
        Card t = game.room.cards[j];
        game.room.cards[j] = game.room.cards[i];
        game.room.cards[i] = t;
    }

    // move the deck by the room size to accomodate the cards
    for (int i = game.deck.size - 1; i >= 0; i--) {
        game.deck.cards[i + game.room.size] = game.deck.cards[i];
    }
    game.deck.size += game.room.size;

    // move cards from room to deck
    int i = 0;
    for (int j = 0; j < GAME_ROOM_CAPACITY; j++) {
        if (game.room.cards[j] == CARD_BLANK) { continue; }
        game.deck.cards[i] = game.room.cards[j];
        game.room.cards[j] = CARD_BLANK;
        i++;
    }

    game.room.size = 0;
}

void room_pick_card(int idx) {
    if (game.room.cards[idx] == CARD_BLANK) { return; }

    game.room.cards[idx] = CARD_BLANK;
    game.room.size--;
}

ClickInteractable clicked_rect() {
    Vector2 mouse = GetMousePosition();
    for (int i = 0; i < CLICK_NONE; i++) {
        if (CheckCollisionPointRec(mouse, game.clickables[i])) {
            return (ClickInteractable)i;
        }
    }

    return CLICK_NONE;
}

void debug_print() {
    TraceLog(LOG_INFO,
        "GAME:\nnothing\n"
        "ROOM:\n"
        "size: %d\n"
        "DECK:\n"
        "size: %d\n"
        "capacity: %d\n",
        game.room.size,
        game.deck.size,
        game.deck.capacity
    );
}

void game_logic() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        ClickInteractable action = clicked_rect();
        switch (action) {
        case CLICK_ROOM_1:
        case CLICK_ROOM_2:
        case CLICK_ROOM_3:
        case CLICK_ROOM_4:
            room_pick_card(action);
            debug_print();
            break;
        
        default:
            break;
        }
    }

    if (IsKeyPressed(KEY_SPACE)) {
        room_draw();
        debug_print();
    }

    if (IsKeyPressed(KEY_R)) {
        room_run();
        debug_print();
    }
}