#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sprites.h"
#include "function_list.h"

int main() {
    srand(time(NULL));
    game_board board;
    ship player;
    ast asts[20]; // max ast number
    junk junklist[20]; //max

    int astcount = 0;
    int junkcount = 0;
    int level = 0;
    int difficulty = difficulty_tweak(); // ask player for difficulty


    // start the game
    initialise_game(&board, &player, asts, junklist, &astcount, &junkcount, difficulty, &level);
    int score = (player.junk_collected + level + player.fuel) * difficulty;
    while (player.health > 0 && player.fuel > 0 && level <= 5) {
        display_board(&board);
        printf("fuel: %d  lives: %d  junk collected: %d\n", player.fuel, player.health, player.junk_collected);
        take_turn(&board, &player, asts, astcount, junklist, junkcount, level, difficulty);


        if (player.junk_collected >= junkcount) {
            level++;
            printf("\n========= level %d ========\n", level);
            initialise_game(&board, &player, asts, junklist, &astcount, &junkcount, difficulty, &level);
        }
        if (level > 5) {
            printf("\n");
            printf("=====================================\n");
            printf("         GAME OVER YOU WIN\n");
            printf("=====================================\n");
            printf("Final Score:         %d\n", score);
            printf("Junk Collected:      %d\n", player.junk_collected);
            printf("Difficulty Level:    %d\n", difficulty);
            printf("=====================================\n");
            printf("  Thanks for playing Space Explorer! \n");
            printf("=====================================\n\n");
            char name[name_len];
            printf("Enter your name: ");
            fflush(stdin);
            fgets(name, name_len, stdin);
            name[strcspn(name, "\n")] = '\0';

        }
        if (player.fuel <= 0) {
            printf("\n");
            printf("=====================================\n");
            printf("         GAME OVER YOU LOOSE\n");
            printf("=====================================\n");
            printf("         YOU RAN OUT OF FUEL\n");
            printf("=====================================\n");
            printf("final Score:         %d\n", score);
            printf("junk Collected:      %d\n", player.junk_collected);
            printf("difficulty Level:    %d\n", difficulty);
            printf("=====================================\n");
            printf("  Thanks for playing Space Explorer! \n");
            printf("=====================================\n\n");
            char name[name_len];
            printf("Enter your name: ");
            fflush(stdin);
            fgets(name, name_len, stdin);
            name[strcspn(name, "\n")] = '\0';
        }


        if (player.health <= 0) {
            printf("\n");
            printf("=====================================\n");
            printf("         GAME OVER YOU LOOSE\n");
            printf("=====================================\n");
            printf("       YOU TOOK TOO MUCH DAMAGE\n");
            printf("=====================================\n");
            printf("Final Score:         %d\n", score);
            printf("Junk Collected:      %d\n", player.junk_collected);
            printf("Difficulty Level:    %d\n", difficulty);
            printf("=====================================\n");
            printf("  Thanks for playing Space Explorer! \n");
            printf("=====================================\n\n");
            char name[name_len];
            printf("Enter your name: ");
            fflush(stdin);
            fgets(name, name_len, stdin);
            name[strcspn(name, "\n")] = '\0';
                }
            }



    return 0;
}