#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sprites.h"
void display_board(game_board *board) {
    for (int y = -1; y <= board_size; y++) {
        for (int x = -1; x <= board_size; x++) {
            if (y == -1 || y == board_size || x == -1 || x == board_size) {
                printf(" x ");
            }
            else {
                printf(" %c ", board->grid[y][x].entity);
            }
        }
        printf("\n");
    }
}
void initialise_game(game_board *board, ship *player, ast ast[], junk junklist[], int *astcount, int *junkcount, int difficulty, int *level) {
    srand(time(NULL));

    *junkcount = *level + difficulty + (rand() % 15 + 1);
    *astcount = *junkcount + (*level + difficulty);

    printf("junk count = %d\n", *junkcount);
    printf("ast count = %d\n", *astcount);
    printf("initialising game board\n");

    // Clear board
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            board->grid[y][x].entity = empty_sprite;
            board->grid[y][x].empty = 1; // board starts empty
        }
    }

    // Place ship
    player->pos.x = board_size / 2;
    player->pos.y = board_size / 2;
    player->fuel = 100;
    player->health = 3;
    player->junk_collected = 0;

    board->grid[player->pos.y][player->pos.x].entity = ship_sprite;
    board->grid[player->pos.y][player->pos.x].empty = 0;

    printf("ship located at (%d, %d)\n", player->pos.x, player->pos.y);

    // Place asts
    for (int i = 0; i < *astcount; i++) {
        int x, y;
        do {
            x = rand() % board_size;
            y = rand() % board_size;
        } while (!board->grid[y][x].empty);

        ast[i].pos.x = x;
        ast[i].pos.y = y;
        ast[i].move_x = (rand() % 3) - 1;
        ast[i].move_y = (rand() % 3) - 1;

        if (ast[i].move_x == 0 && ast[i].move_y == 0) {
            ast[i].move_x = 1;
        }

        ast[i].hit = 1;

        board->grid[y][x].entity = ast_sprite;
        board->grid[y][x].empty = 0;

        printf("ast %d located at (%d, %d)\n", i + 1, x, y);
    }

    // Place junk
    for (int i = 0; i < *junkcount; i++) {
        int x, y;
        do {
            x = rand() % board_size;
            y = rand() % board_size;
        }
        while (!board->grid[y][x].empty);

        junklist[i].pos.x = x;
        junklist[i].pos.y = y;
        junklist[i].present = 1;

        board->grid[y][x].entity = junk_sprite;
        board->grid[y][x].empty = 0;

        printf("junk %d located at (%d, %d)\n", i + 1, x, y);
    }

    display_board(board);
}

void main(void) {
    srand(time(NULL));
    game_board board;
    ship player;
    ast asts[20]; // max ast number
    junk junklist[20]; //max

    int astcount = 0;
    int junkcount = 0;
    int level = 1;
    int difficulty = 1; // ask player for difficulty


    // start the game
    initialise_game(&board, &player, asts, junklist, &astcount, &junkcount, difficulty, &level);
}