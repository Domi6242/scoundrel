#ifndef SCOUNDREL_GLOBALS_H
#define SCOUNDREL_GLOBALS_H

// #define GAME_SCREEN_W 320
// #define GAME_SCREEN_H 240
#define GAME_SCREEN_W 640
#define GAME_SCREEN_H 480
#define CARD_W 48
#define CARD_H 64
#define DECK_CAPACITY 44

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

#endif