#include "types.h"
#include "util.h"
#include <memory.h>
#include <stdio.h>

void printLetterMap(FILE *stream, struct WORDLE_LetterMap *letter_map)
{
    if(letter_map)
    {
        for(int i = 0; i < 26; i++)
        {
            fprintf(stream, "%c: ", 'a'+i);
            for(int j = 0; j < 8; j++)
            {
                fprintf(stream, "%d", (letter_map->visited_letters[i] & (0b10000000 >> j)) > 0);
            }
            fprintf(stream, "\n");
        }
    }
    else
    {
        fprintf(stream, "Letter map is NULL\n");
    }
}

void initialize_letter_map(struct WORDLE_LetterMap *letter_map)
{
    if(letter_map)
    memset(letter_map, 0, sizeof(struct WORDLE_LetterMap));
}

void set_letter_exists(struct WORDLE_LetterMap *letter_map, unsigned char letter)
{
    if(letter_map)
    {
        letter_map->visited_letters[asciiTo0To26(letter)] |= 0b10000000;
    }
}

void set_letter_exists_at(struct WORDLE_LetterMap *letter_map, unsigned char letter, unsigned int position)
{
    if(letter_map)
    {
        letter_map->visited_letters[asciiTo0To26(letter)] |= (0b01000000 >> position);
        letter_map->visited_letters[asciiTo0To26(letter)] |= 0b10000000;
    }
}

void bitwise_or_maps(struct WORDLE_LetterMap *map1, struct WORDLE_LetterMap *map2, struct WORDLE_LetterMap *result)
{
    if(map1 && map2 && result)
    {
       // each map has 26 bytes
       // so we take a 8 bytes 3 times to OR them together
       // and then take the last 2 bytes to OR them together
        __UINT64_TYPE__ * map1_64 = (__UINT64_TYPE__ *)map1;
        __UINT64_TYPE__ * map2_64 = (__UINT64_TYPE__ *)map2;
        __UINT64_TYPE__ * result_64 = (__UINT64_TYPE__ *)result;
        result_64[0] = map1_64[0] | map2_64[0];
        result_64[1] = map1_64[1] | map2_64[1];
        result_64[2] = map1_64[2] | map2_64[2];

        // take the last 2 bytes
        __UINT16_TYPE__ * map1_16 = (__UINT16_TYPE__ *)(&(map1->visited_letters[24]));
        __UINT16_TYPE__ * map2_16 = (__UINT16_TYPE__ *)(&(map2->visited_letters[24]));
        __UINT16_TYPE__ * result_16 = (__UINT16_TYPE__ *)(&(result->visited_letters[24]));
        result_16[0] = map1_16[0] | map2_16[0];

    }
}

void add_response_from_word(struct WORDLE_LetterMap *letter_map, unsigned char word[5], unsigned char response[5])
{
    if(letter_map && word && response)
    {
        for(int i = 0; i < 5; i++)
        {
            if(response[i] == 'e')
            
                set_letter_exists(letter_map, word[i]);
                
            
            else if(response[i] == 'c')
            
                set_letter_exists_at(letter_map, word[i], i);
            
        }
    }
}
