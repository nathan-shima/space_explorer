#ifndef function_list_H //sets the name of the library so i can call it in the main game file later
#define function_list_H
#include "sprites.h"

// all functions are in order of when they appear
// store function declarations here

// clamp function to limit number of junk and asteroids to the range i set
int minmax(int value, int min, int max);

//set the difficulty
int difficulty_tweak(void);

// this function starts the game
void initialise_game(game_board *board, ship *player, asteroid ast[], junk junklist[], int *astcount, int *junkcount, int difficulty);

// this function displays the game board
void display_board(game_board *board);

#endif