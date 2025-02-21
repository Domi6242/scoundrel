#include "draw.h"
#include "game.h"

Texture2D cards_tileset;

void draw_card(Vector2 pos, Card card) {
    if (card == CARD_BACK) {
        static const Rectangle back_text = {0, 0, CARD_W, CARD_H};
        DrawTextureRec(cards_tileset, back_text, pos, WHITE);
        return;
    }

    // skip drawing if it's not a valid card
    if (card < CARD_2_OF_HEARTS || card >= CARD_COUNT) {
        return;
    }

    Rectangle card_text = {get_rank(card) * CARD_W, get_suit(card) * CARD_H, CARD_W, CARD_H};
    DrawTextureRec(cards_tileset, card_text, pos, WHITE);
}

void draw_init() {
    cards_tileset = LoadTexture("./assets/cardtile.png");
}

void draw_frame() {
    ClearBackground(RAYWHITE);


    int row_fit = GAME_SCREEN_W / CARD_W;
    for (int i = 0; i < DECK_CAPACITY; i++) {
        Vector2 pos = {
            (i % row_fit) * CARD_W,
            (i / row_fit) * CARD_H
        };
        draw_card(pos, get_deck()->cards[i]);
    }
}

void draw_deinit() {
    UnloadTexture(cards_tileset);
}