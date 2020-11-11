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
#include <linux/fb.h>

#define SCREEN_X 320
#define SCREEN_Y 240
#define SCREEN_SIZE (SCREEN_X*SCREEN_Y)

#define OFFSET_X 60
#define OFFSET_Y 10
#define IMG_X 20
#define IMG_Y IMG_X

void screen_init();

void print_image(); //test an image
void print_sprite(const uint16_t *image, uint16_t off_x, uint16_t off_y);
void print_gameboard(const uint16_t *image);

void screen_cleanup();

#endif
