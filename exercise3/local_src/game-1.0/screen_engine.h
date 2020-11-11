#ifndef SCREEN_ENGINE_H
#define SCREEN_ENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <linux/fb.h>

#define SCREEN_X 320
#define SCREEN_Y 240
#define SCREEN_SIZE (SCREEN_X*SCREEN_Y)

#define PAD_COLOR 0x7777
#define BG_COLOR 0x0000
#define SNK_COLOR 0x03e8

#define BOARD_SIDE 20 //in the matrix
#define BOARD_SCREEN SCREEN_Y //projected on screen
#define BOARD_RATIO (BOARD_SCREEN/BOARD_SIDE)

#define BOARD_SNAKE_BODY 1
#define BOARD_APPLE 2

void screen_init();
void screen_update(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void print_image(); //test an image
void print_sprite(const uint16_t *image, uint16_t off_x, uint16_t off_y);
void print_gameboard(uint16_t *image);
void print_test_board();
uint16_t color(uint16_t tileState);
void color_tile(uint16_t *gameboard, uint8_t x, uint8_t y);

void screen_cleanup();

#endif
