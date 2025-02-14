
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>



int main()
{
    struct WORDL_GAME_PLAYER player;
    //printf("hello!");
    initialize_game(&player);
    unsigned char guess[WORDLE_WORD_LENGTH];
    unsigned char response[WORDLE_WORD_LENGTH];
    printf("hello!");
    int game_over = 0;
    while(1)
    {   
        printf("Hello=");
        printLetterMap(stdout, &(player.letterMapComplete));
        if(game_over == 1 || game_over == -1)
        {
            break;
        }
        get_wordle_guess_stdin(guess);
        player.guesses_left--;
        get_wordle_response_stdin(response);
        add_response_from_word(&(player.letterMapComplete), (unsigned char*)guess, (unsigned char*)response);
        game_over = is_game_over(&player);
        printf("Game is over: %d\n", game_over);
    }
}