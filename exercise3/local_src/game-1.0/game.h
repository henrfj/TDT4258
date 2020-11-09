#ifndef GAME_H
#define GAME_H

/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/////////////////////////////
#include "test.h"
#include "gamepad_engine.h"
#include "screen_engine.h"
#include "sound_engine.h"


#define BOARD_SIZE 20
#define MAX_SNAKE 15

static int BOARD[BOARD_SIZE][BOARD_SIZE];
static int SNAKE_BODY[MAX_SNAKE][2] //keeps track of the snake
static int TAIL_INDEX;




void game_loop();
int get_input();
void spawn_fruit();
void initialize_snake(int headPos);

#endif

