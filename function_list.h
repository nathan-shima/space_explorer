#ifndef function_list_H //sets the name of the library so i can call it in the main game file later
#define function_list_H
#include "sprites.h"

// all functions are in order of when they appear
// store function declarations here

//set the difficulty
int difficulty_tweak(void);

// this function starts the game
void initialise_game(game_board *board, ship *player, ast ast[], junk junklist[], int *astcount, int *junkcount, int difficulty, int *level);

// this function displays the game board
void display_board(game_board *board);

// this function will move the ship
void player_move(game_board *board, ship *player, junk junklist[], int junkcount, ast asts[], int astcount);

// this function adds random movement to asts
void ast_move(game_board *board, ast asts[], int astcount, ship *player, int level, int difficulty, junk junklist[], int junkcount);

// this function moves the junk
void junk_move(game_board *board, junk junklist[], int junkcount, int level, int difficulty, ast asts[], int astcount);

//this function adds all movement into a single function to streamline main
void take_turn(game_board *board, ship *player, ast asts[], int astcount, junk junklist[], int junkcount, int level, int difficulty);

// print end screen depending on conditions met
void end_game(int level, int difficulty, int score);

#endif