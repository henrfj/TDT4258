#ifndef SCREEN_ENGINE_H
#define SCREEN_ENGINE_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <errno.h>
#include <linux/fb.h>

#define SCREEN_X 320
#define SCREEN_Y 240
#define SCREEN_SIZE (SCREEN_X*SCREEN_Y)

#define IMG_X 20
#define IMG_Y IMG_X

void print_image();

#endif
