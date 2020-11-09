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

int BOARD[BOARD_SIZE][BOARD_SIZE];
void game_loop();
int get_input();
void spawn_fruit();

#endif

