#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function_list.h"

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

// this function starts the game
void initialise_game(game_board *board, ship *player, asteroid *ast, junk junklist[], int junkcount){

  //for loop to clear the board
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