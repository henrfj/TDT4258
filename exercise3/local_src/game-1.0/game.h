#ifndef GAME_H
#define GAME_H
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/////////////////////////////
#include "test.h"
#include "gamepad_engine.h"
#include "screen_engine.h"
#include "sound_engine.h"
/////////////////////////////
#define BOARD_SIZE 20
#define MAX_SNAKE 15
#define TRUE 1
#define FALSE 0
/////////////////////////////
//TODO: make static
uint16_t BOARD[BOARD_SIZE][BOARD_SIZE];
uint16_t SNAKE_BODY[MAX_SNAKE][2];
uint16_t TAIL_INDEX;
/////////////////////////////
void game_loop();
int get_input();
void reorder_snake(uint8_t head[], uint8_t grow);
int spawn_fruit();
void initialize_snake(uint8_t headPos[2]);
int snake_direction(uint8_t direction);
void snake_movement(uint8_t headPos[2], uint8_t direction);
void print_board();
/////////////////////////////
#endif

