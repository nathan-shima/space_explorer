#ifndef functions_H //sets the name of the library so i can call it in the main game file later
#define functions_H
#include "sprites.h"

// store function declarations here

// this function starts the game
void initialise_game(game_board *board, ship *player, asteroid *ast, junk junklist[], int junkcount);

// this function displays the game board
void display_board(game_board *board);

#endif