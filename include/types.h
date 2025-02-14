#ifndef TYPES_H

struct WORDLE_LetterMap {
    /**
     * 8 bits per letter. First bit is the existence of the letter itself, the next 5 bits are flags for the 5 possible positions of the letter in the word.
     */
    unsigned char visited_letters[26]; //  initialize this with 0
};

/**
 * Initialize the letter map with all letters set to 0.
 * @param letter_map The letter map to initialize.
 * @return void
 */
void initialize_letter_map(struct WORDLE_LetterMap *letter_map);
/**
 * Set the letter in the letter map.
 * @param letter_map The letter map to set the letter in.
 */
void letter_exists(struct WORDLE_LetterMap *letter_map, unsigned char letter);
/**
 * Set the letter in the letter map at the given position.
 * @param letter_map The letter map to set the letter in.
 * @param letter The letter to set.
 * @param position The position to set the letter in.
 */
void letter_exists_at(struct WORDLE_LetterMap *letter_map, unsigned char letter, int position);

/**
 * Bitwise OR two letter maps together.
 * @param map1 The first map.
 * @param map2 The second map.
 * @param result The result of the bitwise OR.
 * @return void
 */
void bitwise_or_maps(struct WORDLE_LetterMap *map1, struct WORDLE_LetterMap *map2, struct WORDLE_LetterMap *result);

char charsByOccurence[26] = {'e', 'a', 'r', 'i', 'o', 't', 'n', 's', 'l', 'c', 'u', 'd', 'p', 'm', 'h', 'g', 'b', 'f', 'y', 'w', 'k', 'v', 'x', 'z', 'j', 'q'};

#define TYPES_H
#endif