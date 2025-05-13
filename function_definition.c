#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function_list.h"

int minmax(int value, int min, int max) {
  if (value < min)
    return min;
  else if (value > max)
    return max;
  else
    return value;
}

int difficulty_tweak(void) {
	int difficulty;
  do {
        printf("please enter the difficulty (easy = 1, medium = 2, hard = 3) : ");
        scanf("%d", &difficulty);
	}
   	while (difficulty < 1 || difficulty > 3);
    printf("difficulty = %d\n", difficulty); //displays difficulty to show the function works
    return difficulty;
}


// this function starts the game
void initialise_game(game_board *board, ship *player, asteroid ast[], junk junklist[], int *astcount, int *junkcount, int difficulty) {
    srand(time(NULL));

    // Difficulty affects number of entities
    *junkcount = minmax((rand() % 15 + 1) - difficulty * 2, 1, 15);
    *astcount = *junkcount + 5;

    printf("junk count = %d\n", *junkcount);
    printf("asteroid count = %d\n", *astcount);
    printf("initialising game board\n");

    // Clear board
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            board->grid[y][x].entity = empty_sprite;
            board->grid[y][x].empty = 0;
        }
    }

    // Place ship at center
    player->pos.x = board_size / 2;
    player->pos.y = board_size / 2;
    player->fuel = 100;
    player->health = 3;
    player->junk_collected = 0;

    board->grid[player->pos.y][player->pos.x].entity = ship_sprite;
    board->grid[player->pos.y][player->pos.x].empty = 1;

    printf("ship located at (%d, %d)\n", player->pos.x, player->pos.y);

    // Add asteroids
    for (int i = 0; i < *astcount; i++) {
        int x, y;
        do {
            x = rand() % board_size;
            y = rand() % board_size;
        } while (board->grid[y][x].empty);

        ast[i].pos.x = x;
        ast[i].pos.y = y;
        ast[i].move_x = (rand() % 3) - 1;
        ast[i].move_y = (rand() % 3) - 1;

        if (ast[i].move_x == 0 && ast[i].move_y == 0) {
            ast[i].move_x = 1;
        }

        ast[i].hit = 1;

        board->grid[y][x].entity = asteroid_sprite;
        board->grid[y][x].empty = 1;

        printf("asteroid %d located at (%d, %d)\n", i + 1, x, y);
    }

    // Add junk
    for (int i = 0; i < *junkcount; i++) {
        int x, y;
        do {
            x = rand() % board_size;
            y = rand() % board_size;
        } while (board->grid[y][x].empty);

        junklist[i].pos.x = x;
        junklist[i].pos.y = y;
        junklist[i].present = 1;

        board->grid[y][x].entity = junk_sprite;
        board->grid[y][x].empty = 1;

        printf("junk %d located at (%d, %d)\n", i + 1, x, y);
    }

    display_board(board);
}



// display the board
void display_board(game_board *board){
for (int y = -1; y <= board_size; y++){
  for (int x = -1; x <= board_size; x++){
    if (y == -1 || y == board_size|| x == -1 || x == board_size){
      printf(" x ");
      }
     else{
       printf(" %c ", board->grid[y][x].entity);
       }
    }
    printf("\n");
  }
}