#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sprites.h"
#include "function_list.h"

int main() {
    srand(time(NULL));
    game_board board;
    ship player;
    ast asts[20]; // max ast number
    junk junklist[20]; //max
    char direction;

    int astcount = 0;
    int junkcount = 0;
    int level = 0;
    int difficulty = difficulty_tweak(); // Ask player for difficulty


    // start the game
    initialise_game(&board, &player, asts, junklist, &astcount, &junkcount, difficulty, &level);
    int score = (player.junk_collected + level + player.fuel) * difficulty;
    while (player.health > 0 && player.fuel > 0) {
        display_board(&board);
        printf("fuel: %d  lives: %d\n", player.fuel, player.health);
        take_turn(&board, &player, asts, astcount, junklist, junkcount, level, difficulty);


        // check for junk collection
        for (int i = 0; i < junkcount; i++) {
            if (junklist[i].present && junklist[i].pos.x == player.pos.x && junklist[i].pos.y == player.pos.y) {
                junklist[i].present = 0;
                player.junk_collected++;
                player.fuel += 10;
                if (player.fuel > 100) {
                    player.fuel = 100;
                }
                printf("collected junk! Total: %d\n", player.junk_collected);
            }
        }

        if (player.junk_collected >= junkcount) {
            level++;
            printf("\n========= level %d ========\n", level);
            initialise_game(&board, &player, asts, junklist, &astcount, &junkcount, difficulty, &level);
        }
        for (int i = 0; i < astcount; i++) {
            if (asts[i].hit && asts[i].pos.x == player.pos.x && asts[i].pos.y == player.pos.y) {
                player.health--;
                printf("Hit by ast! Health: %d\n", player.health);
                asts[i].hit = 0;
            }
        }
    }





    return 0;
}