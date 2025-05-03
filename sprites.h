#ifndef sprites_H //sets the name of the library so i can call it in the main game file later
#define sprites_H

// define the game board
#define board_size 18

// sprites to be placed on the game board
#define ship_sprite 'S'
#define junk_sprite 'J'
#define asteroid_sprite 'A'
#define empty_sprite ' '

// structures made below
// making grid structure
typedef struct {
  int x;
  int y;
} position;

// create the ship structure
typedef struct {
  position pos;
  int fuel;
  int health;
  int junk_collected;
} ship;

// create structure for asteroid
typedef struct {
  position pos;
  int move_x;
  int move_y;
  int hit; // 1 if not hit by asteroid or junk
} asteroid;

//created structure for junk
typedef struct {
  position pos;
  int present; // 1 if not collected 0 if it is collected
} junk;

// make structure for individual cells on the game board
typedef struct {
  char entity;
  int empty; // 0 for empty 1 for full
} space;

typedef struct {
  space grid[board_size][board_size];
} game_board;



#endif