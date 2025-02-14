#ifndef NPC_H
/**
 * @file npc.h
 * @brief Functionality for playing against an unknown wordle.
 */

#include "types.h"

const int WORDLE_GUESSES = 6;
const int WORDLE_WORD_LENGTH = 5;

struct WORDL_GAME_PLAYER
{
    struct WORDLE_LetterMap letterMapComplete;
    int guesses_left;
};

struct WORDL_Response_Giver
{
    struct WORDLE_LetterMap responseMap;
    unsigned char word[WORDLE_WORD_LENGTH];
};

struct WORDL_GAME
{
    struct WORDL_GAME_PLAYER player;
    struct WORDL_Response_Giver response_giver;
};

/**
 * Initialize the game with the given word.
 * @param game The game to initialize.
 * @param word The word to initialize the game with.
 * @return void
 */
void initialize_game(struct WORDL_GAME *game, unsigned char word[WORDLE_WORD_LENGTH]);

/**
 * Take a guess in the game. The game will update the player's guesses left and the response giver's response map, which then gets added "additive" to the players map.
 */
void take_a_guess(struct WORDL_GAME *game, unsigned char guess[WORDLE_WORD_LENGTH]);

/**
 * Check if the game is over.
 * @param game The game to check.
 * @return 1 if the game is WON, -1 if LOST, 0 otherwise
 */
int is_game_over(struct WORDL_GAME *game);

#define NPC_H
#endif