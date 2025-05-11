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

int difficulty_tweak(int difficulty) {
	do {
          printf("please enter the difficulty (easy = 1, medium = 2, hard = 3) : ");
          scanf("%d", &difficulty);
	}
   	while (difficulty < 1 || difficulty > 3);
    printf("difficulty = %d\n", difficulty); //displays difficulty to show the function works
    return difficulty;
}




// this function starts the game
void initialise_game(game_board *board, ship *player, asteroid ast[], junk junklist[],int astcount, int junkcount, int difficulty) {
  srand(time(NULL));

  //setting the number of junk and asteroids based on difficulty selected
  junkcount = minmax((rand() % 15 + 1) - difficulty * 2, 1, 15);
  asteroid

  //for loop to clear the board (will do this every time game is run)
  for (int y = 0; y < board_size; y++){
    for (int x = 0; x < board_size; x++){
      board->grid[y][x].entity = empty_sprite;
      board->grid[y][x].empty = 0;
    }
  }

  //add ship to the board and set starting values
  player->pos.x = board_size/2;
  player->pos.y = board_size/2;
  player->fuel = 100;
  player->health = 3;
  player->junk_collected = 0;

  board->grid[player->pos.y][player->pos.x].entity = ship_sprite;
  board->grid[player->pos.y][player->pos.x].empty = 1;



}

// display the board
void display_board(game_board *board){
for (int y = -1; y <= board_size; y++){
  for (int x = -1; x <= board_size; x++){
    if (y == -1 || y == board_size|| x == -1 || x == board_size){
      printf("x");
      }
     else{
       printf("%c", board->grid[y][x].entity);
       }
    }
    printf("\n");
  }
}