#include "game.h"
#include <memory.h>
#include <stdio.h>

void initialize_game(struct WORDL_GAME_PLAYER *player)
{
    if(player)
    {
        memset(player, 0, sizeof(struct WORDL_GAME_PLAYER));
        player->guesses_left = WORDLE_GUESSES;
        fprintf(stdout, "Welcome to Wordle! You have %d guesses to guess the word.\n", WORDLE_GUESSES);
    }
}

int validate_word(unsigned char *input)
{
    if(input)
    {
        int count = 0;
        while(input[0] != '\0' && count < WORDLE_WORD_LENGTH)
        {
            if(input[0] == '\n' || input[0] == '\r')
            {
                continue;
            }
            count++;
            input++;
        }
        if(count == WORDLE_WORD_LENGTH)
        {
            return 1;
        }
    }
    return 0;
}

int validate_response(unsigned char *input)
{
    
    if(input)
    {
        int count = 0;
        while(input[0] != '\0')
        {
            if(input[0] == 'e' || input[0] == 'c' || input[0] == 'n')
            {
                input++;
                count++;
                continue;
            }
            else if(input[0] == '\n' || input[0] == '\r')
            {
                input++;
                continue;
            }
            else
            {
                return 0;
            }
        }
        if(count == WORDLE_WORD_LENGTH)
            return 1;
        
    }
    return 0;
}

void get_wordle_response_stdin(unsigned char response[WORDLE_WORD_LENGTH])
{
    const int MAX_BUFFER_SIZE = 1024;
    unsigned char BUFFER[MAX_BUFFER_SIZE];
    fprintf(stdout, "For each of the %d characters, enter 'e' for exists, 'c' for correct position or 'n' for not exists.\n", WORDLE_WORD_LENGTH);
    fprintf(stdout, "Example: 'eecn' means the first two characters exist, the third is in the correct position and the last one does not exist.\n");
    int invalid = 1;
    while(invalid)
    {
        fprintf(stdout, "Enter: ");
        fgets((char*)BUFFER, MAX_BUFFER_SIZE, stdin);
        invalid = !validate_response(BUFFER);
        if(invalid) fprintf(stdout, "Invalid response. Please enter a %d letter response.\n", WORDLE_WORD_LENGTH);
    }
    strncpy((char*)response, (char*)BUFFER, WORDLE_WORD_LENGTH);
    
}

void get_wordle_guess_stdin(unsigned char guess[WORDLE_WORD_LENGTH])
{
    const int MAX_BUFFER_SIZE = 1024;
    unsigned char BUFFER[MAX_BUFFER_SIZE];
    int invalid = 1;
    while(invalid)
    {
        fprintf(stdout, "Enter your guess: ");
        fgets((char*)BUFFER, MAX_BUFFER_SIZE, stdin);
        invalid = !validate_word(BUFFER);
        if(invalid) fprintf(stdout, "Invalid guess. Please enter a %d letter word.\n", WORDLE_WORD_LENGTH);
    }
    strncpy((char*)guess, (char*)BUFFER, WORDLE_WORD_LENGTH);
    
}

int is_game_over(struct WORDL_GAME_PLAYER *player)
{
    int correct_count = 0;
    if(player)
    {
        for(int i = 0; i < 26; i++)
        {
            if(player->letterMapComplete.visited_letters[i] & 0b01000000)
            {
                correct_count++;
            }
            if(player->letterMapComplete.visited_letters[i] & 0b00100000)
            {
                correct_count++;
            }
            if(player->letterMapComplete.visited_letters[i] & 0b00010000)
            {
                correct_count++;
            }
            if(player->letterMapComplete.visited_letters[i] & 0b00001000)
            {
                correct_count++;
            }
            if(player->letterMapComplete.visited_letters[i] & 0b00000100)
            {
                correct_count++;
            }
            if(correct_count == WORDLE_WORD_LENGTH)
            {
                return 1;
            }
        }
        if(player->guesses_left == 0)
        {
            return -1;
        }
    }
    return 0;
}
