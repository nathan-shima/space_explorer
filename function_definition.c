#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function_list.h"

int difficulty_tweak(void) {
    int difficulty;
    do {
        printf("please enter the difficulty (easy = 1, medium = 2, hard = 3) : ");
        scanf("%d", &difficulty);
    } while (difficulty < 1 || difficulty > 3);

    printf("difficulty = %d\n", difficulty);
    return difficulty;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------------------------------------------------------
void player_move(game_board *board, ship *player, junk junklist[], int junkcount, ast asts[], int astcount) {
    int dx = 0, dy = 0;
    char direction;
    printf("use w a s d to move: ");
    scanf(" %c", &direction);
    printf("\n");

    switch (direction) {
        case 'w':
        case 'W':
        dy = -1;
        break;

        case 's':
        case 'S':
        dy = 1;
        break;

        case 'a':
        case 'A':
        dx = -1;
        break;

        case 'd':
        case 'D':
        dx = 1;
        break;

        default:
            printf("invalid direction\n");
        return;
    }

    // New proposed position
    int new_x = (player->pos.x + dx + board_size) % board_size;
    int new_y = (player->pos.y + dy + board_size) % board_size;

    char target = board->grid[new_y][new_x].entity;

    // asteroid and junk collisions
    if (target == junk_sprite) {
        printf("junk collected\n");
        player->junk_collected++;
        player->fuel += 10;
        // Mark junk as not present
        for (int i = 0; i < junkcount; i++) {
            if (junklist[i].present &&
                junklist[i].pos.x == new_x &&
                junklist[i].pos.y == new_y) {
                junklist[i].present = 0;
                break;
                }
        }
    }
    else if (target == ast_sprite) {
        printf("hit an asteroid\n");
        player->health--;

        // Remove ast
        for (int i = 0; i < astcount; i++) {
            if (asts[i].pos.x == new_x &&
                asts[i].pos.y == new_y) {
                asts[i].pos.x = -1;
                asts[i].pos.y = -1;
                break;
                }
        }
    }

    // Clear previous position
    board->grid[player->pos.y][player->pos.x].entity = empty_sprite;
    board->grid[player->pos.y][player->pos.x].empty = 1;

    // Move player
    player->pos.x = new_x;
    player->pos.y = new_y;
    player->fuel--;

    // Place ship at new position
    board->grid[new_y][new_x].entity = ship_sprite;
    board->grid[new_y][new_x].empty = 0;
}
//----------------------------------------------------------------------------------------------------------------------------------
void junk_move(game_board *board, junk junklist[], int junkcount, int level, int difficulty, ast asts[], int astcount) {
    for (int i = 0; i < junkcount; i++) {
        if (!junklist[i].present)
            continue;

        // Calculate new position
        int new_x = (junklist[i].pos.x + junklist[i].move_x + board_size) % board_size;
        int new_y = (junklist[i].pos.y + junklist[i].move_y + board_size) % board_size;

        // Check for collision with asteroid
        int coll = 0;
        for (int j = 0; j < astcount; j++) {
            if (asts[j].pos.x == new_x && asts[j].pos.y == new_y) {
                coll = 1;
                break;
            }
        }

        if (!coll) {
            // Clear previous position
            board->grid[junklist[i].pos.y][junklist[i].pos.x].entity = empty_sprite;
            board->grid[junklist[i].pos.y][junklist[i].pos.x].empty = 1;

            // Apply move
            junklist[i].pos.x = new_x;
            junklist[i].pos.y = new_y;
        }

        // Update board regardless (same spot if blocked)
        board->grid[junklist[i].pos.y][junklist[i].pos.x].entity = junk_sprite;
        board->grid[junklist[i].pos.y][junklist[i].pos.x].empty = 0;

        // Random movement adjustment
        int changeChance = 5 + (level * difficulty);
        if (rand() % 100 < changeChance) {
            junklist[i].move_x = (rand() % 3) - 1;
            junklist[i].move_y = (rand() % 3) - 1;
            if (junklist[i].move_x == 0 && junklist[i].move_y == 0) {
                junklist[i].move_x = 1; // ensure movement
            }
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------

void ast_move(game_board *board, ast asts[], int astcount, ship *player, int level, int difficulty, junk junklist[], int junkcount) {
    for (int i = 0; i < astcount; i++) {
        // new position
        int new_x = (asts[i].pos.x + asts[i].move_x + board_size) % board_size;
        int new_y = (asts[i].pos.y + asts[i].move_y + board_size) % board_size;

        // check for collision with junk
        int coll = 0;
        for (int j = 0; j < junkcount; j++) {
            if (junklist[j].present && junklist[j].pos.x == new_x && junklist[j].pos.y == new_y) {
                coll = 1;
                break;
            }
        }

        if (!coll) {
            // clear previous position
            board->grid[asts[i].pos.y][asts[i].pos.x].entity = empty_sprite;
            board->grid[asts[i].pos.y][asts[i].pos.x].empty = 1;

            // apply move
            asts[i].pos.x = new_x;
            asts[i].pos.y = new_y;

            // update board
            board->grid[new_y][new_x].entity = ast_sprite;
            board->grid[new_y][new_x].empty = 0;
        }
        else {
            // stops the asteroid
            board->grid[asts[i].pos.y][asts[i].pos.x].entity = ast_sprite;
            board->grid[asts[i].pos.y][asts[i].pos.x].empty = 0;
        }

        // scaled direction change
        int changeChance = 5 + (level * difficulty);
        if (rand() % 100 < changeChance) {
            asts[i].move_x = (rand() % 3) - 1;
            asts[i].move_y = (rand() % 3) - 1;
            if (asts[i].move_x == 0 && asts[i].move_y == 0) {
                asts[i].move_x = 1;
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------
void take_turn(game_board *board, ship *player, ast asts[], int astcount, junk junklist[], int junkcount, int level, int difficulty) {
    player_move(board, player, junklist, junkcount, asts, astcount);
    ast_move(board, asts, astcount, player, level, difficulty, junklist, junkcount);
    junk_move(board, junklist, junkcount, level, difficulty, asts, astcount);
}
//------------------------------------------------------------------------------------------------------------------------------------------------
int sort_scores(const void *a, const void *b) {
    leaderboard *entry1 = (leaderboard *)a;
    leaderboard *entry2 = (leaderboard *)b;
    return entry2->score - entry1->score;
}
//--------------------------------------------------------------------------------------------------------------------------------------------
void save_score(const char *name, int score, int difficulty) {
    leaderboard entries[max_no];
    int index = 0;

    // Read any scores already stored
    FILE *file = fopen("\\C:\\Users\\Natha\\OneDrive - UWE Bristol\\year 1\\sem 2\\programming\\space explorer\\leaderboard.txt", "r");  // Open file in read mode
    if (file) {
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            if (isdigit(line[0])) {  // Find the start of the leaderboard
                int rank, score, difficulty;
                char name[name_len];
                if (sscanf(line, "%d | %s %*[^|]| %d | %d", &rank, name, &score, &difficulty) == 4) {
                    // Format leaderboard table
                    strncpy(entries[index].name, name, name_len);
                    entries[index].score = score;
                    entries[index].difficulty = difficulty;
                    index++;
                }
            }
        }
        fclose(file);
    }

    // Add the current score to the leaderboard
    strncpy(entries[index].name, name, name_len);
    entries[index].score = score;
    entries[index].difficulty = difficulty;
    index++;

    // Sort leaderboard by score in descending order
    qsort(entries, index, sizeof(leaderboard), sort_scores);

    // Write to the leaderboard file
    file = fopen("\\C:\\Users\\Natha\\OneDrive - UWE Bristol\\year 1\\sem 2\\programming\\space explorer\\leaderboard.txt", "w");  // Open file in write mode
    if (!file) {
        printf("Could not open file \\C:\\Users\\Natha\\OneDrive - UWE Bristol\\year 1\\sem 2\\programming\\space explorer\\leaderboard.txt\n");
        return;
    }

    // Write the leaderboard to the file
    fprintf(file, "=========== LEADERBOARD ===========\n");
    fprintf(file, "  RANK | NAME       | SCORE | DIFFICULTY\n");
    fprintf(file, "---------------------------------------\n");
    for (int i = 0; i < index; i++) {
        fprintf(file, " %4d | %-10s | %5d |     %d\n", i + 1, entries[i].name, entries[i].score, entries[i].difficulty);
    }
    fprintf(file, "==============================\n");
    fclose(file);
}
//-----------------------------------------------------------------------------------------------------------------------------------------
void display_leaderboard() {
    FILE *file = fopen("\\C:\\Users\\Natha\\OneDrive - UWE Bristol\\year 1\\sem 2\\programming\\space explorer\\leaderboard.txt", "r");
    if (file == NULL) {
        printf("Could not open file \\C:\\Users\\Natha\\OneDrive - UWE Bristol\\year 1\\sem 2\\programming\\space explorer\\leaderboard.txt\n");
        return;
    }
    char line[100];
    int index = 0;
    while (fgets(line,sizeof(line), file) && index < 16) {
        if (line[0] == '\n') {
            continue;
        }
        printf("%s", line);
        index++;
    }
    fclose(file);
}