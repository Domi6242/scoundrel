#include "math.h"
#include "raylib.h"

/**
 * deck of 60 "cards": 54 + 4 blank + 4 extra aces
 * Get card value from index by using division
 * 0123 = 0, 4567 = Aces1...
 * Get card suit from index by using modulo
 * 0 - Hearts, 1 - Damonds, 2 - Spades, 3 - Clubs
 *
 * tileset:
 *      by IvoryRed on itch.io
 *      https://ivoryred.itch.io/pixel-poker-cards
 */

// #define GAME_SCREEN_W 320
// #define GAME_SCREEN_H 240
#define GAME_SCREEN_W 640
#define GAME_SCREEN_H 480
#define CARD_W 48
#define CARD_H 64
#define DECK_CAPACITY 44

typedef enum Suit { SUIT_HEARTS, SUIT_DIAMONDS, SUIT_SPADES, SUIT_CLUBS } Suit;

typedef enum Card {
    CARD_BACK,
    CARD_BLANK_OF_DIAMONDS,
    CARD_BLANK_OF_SPADES,
    CARD_BLANK_OF_CLUBS,
    CARD_A1_OF_HEARTS,
    CARD_A1_OF_DIAMONDS,
    CARD_A1_OF_SPADES,
    CARD_A1_OF_CLUBS,
    CARD_2_OF_HEARTS,
    CARD_2_OF_DIAMONDS,
    CARD_2_OF_SPADES,
    CARD_2_OF_CLUBS,
    CARD_3_OF_HEARTS,
    CARD_3_OF_DIAMONDS,
    CARD_3_OF_SPADES,
    CARD_3_OF_CLUBS,
    CARD_4_OF_HEARTS,
    CARD_4_OF_DIAMONDS,
    CARD_4_OF_SPADES,
    CARD_4_OF_CLUBS,
    CARD_5_OF_HEARTS,
    CARD_5_OF_DIAMONDS,
    CARD_5_OF_SPADES,
    CARD_5_OF_CLUBS,
    CARD_6_OF_HEARTS,
    CARD_6_OF_DIAMONDS,
    CARD_6_OF_SPADES,
    CARD_6_OF_CLUBS,
    CARD_7_OF_HEARTS,
    CARD_7_OF_DIAMONDS,
    CARD_7_OF_SPADES,
    CARD_7_OF_CLUBS,
    CARD_8_OF_HEARTS,
    CARD_8_OF_DIAMONDS,
    CARD_8_OF_SPADES,
    CARD_8_OF_CLUBS,
    CARD_9_OF_HEARTS,
    CARD_9_OF_DIAMONDS,
    CARD_9_OF_SPADES,
    CARD_9_OF_CLUBS,
    CARD_10_OF_HEARTS,
    CARD_10_OF_DIAMONDS,
    CARD_10_OF_SPADES,
    CARD_10_OF_CLUBS,
    CARD_JACK_OF_HEARTS,
    CARD_JACK_OF_DIAMONDS,
    CARD_JACK_OF_SPADES,
    CARD_JACK_OF_CLUBS,
    CARD_QUEEN_OF_HEARTS,
    CARD_QUEEN_OF_DIAMONDS,
    CARD_QUEEN_OF_SPADES,
    CARD_QUEEN_OF_CLUBS,
    CARD_KING_OF_HEARTS,
    CARD_KING_OF_DIAMONDS,
    CARD_KING_OF_SPADES,
    CARD_KING_OF_CLUBS,
    CARD_ACE_OF_HEARTS,
    CARD_ACE_OF_DIAMONDS,
    CARD_ACE_OF_SPADES,
    CARD_ACE_OF_CLUBS,
    CARD_COUNT
} Card;

static inline Suit get_suit(Card card) { return card % 4; }
static inline int get_rank(Card card) { return card / 4; }

Texture2D cards_tileset;

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

int main() {
    // init
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GAME_SCREEN_W, GAME_SCREEN_H, "scoundrel");
    SetTargetFPS(60);
    cards_tileset = LoadTexture(".assets/cardtile.png");

    RenderTexture2D canvas = LoadRenderTexture(GAME_SCREEN_W, GAME_SCREEN_H);

    init_deck();

    while (!WindowShouldClose()) {
        // Fullscreen logic
        if (IsKeyPressed(KEY_F11)) {
            if (IsWindowFullscreen()) {
                ToggleFullscreen();
                SetWindowSize(GAME_SCREEN_W, GAME_SCREEN_H);
            } else {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                ToggleFullscreen();
            }
        }

        /***************************************************************************************************************
         *
         * Logic
         *
         **************************************************************************************************************/

        /***************************************************************************************************************
         *
         * Drawing
         *
         **************************************************************************************************************/
        BeginDrawing();
        BeginTextureMode(canvas);

        // Drawing phase
        {
            ClearBackground(RAYWHITE);
            // draw deck
            // for (int i = 0; i < 5; i++) {
            //     draw_card((Vector2){10, 20 - i * 2}, CARD_BACK);
            // }

            int row_fit = GAME_SCREEN_W / CARD_W;

            for (int i = 0; i < DECK_CAPACITY; i++) {
                Vector2 pos = {
                    (i % row_fit) * CARD_W,
                    (i / row_fit) * CARD_H
                };
                draw_card(pos, game.deck.cards[i]);
            }
        }

        EndTextureMode();

        /***************************************************************************************************************
         *
         * Letterbox
         *
         **************************************************************************************************************/
        ClearBackground(BLACK);
        float render_scale =
            fmin(GetScreenHeight() / (float)canvas.texture.height, GetScreenWidth() / (float)canvas.texture.width);
        Rectangle render_rect;
        render_rect.width = canvas.texture.width * render_scale;
        render_rect.height = canvas.texture.height * render_scale;
        render_rect.x = (GetScreenWidth() - render_rect.width) / 2.0f;
        render_rect.y = (GetScreenHeight() - render_rect.height) / 2.0f;
        DrawTexturePro(canvas.texture, (Rectangle){0, 0, (float)canvas.texture.width, (float)-canvas.texture.height},
                       render_rect, (Vector2){0, 0}, 0, WHITE);

        EndDrawing();
    }

    UnloadTexture(cards_tileset);
    CloseWindow();

    return 0;
}