#include <stdio.h>
#include <stdlib.h>
#include "sprites.h"
#include "function_list.h"

int main() {
    game_board board;
    ship player;
    asteroid asteroids[20]; // Maximum possible asteroids
    junk junkList[15];      // Maximum possible junk

    int asteroidCount = 0;
    int junkCount = 0;

    int difficulty = difficulty_tweak(); // Ask player for difficulty

    // Correct usage: Pass addresses, not types
    initialise_game(&board, &player, asteroids, junkList, &asteroidCount, &junkCount, difficulty);

    // You can now add your game loop or additional logic here

    return 0;
}