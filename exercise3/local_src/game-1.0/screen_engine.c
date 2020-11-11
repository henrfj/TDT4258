#include "screen_engine.h"
#include "sprites.h"

static int F_screen;
static uint16_t *Screen;

void screen_init() {
	F_screen = open("/dev/fb0", O_RDWR);
	if(F_screen < 0) {
		fprintf(stderr, "Cannot open screen\n");
		exit(-1);
	}
	Screen = mmap(NULL, SCREEN_SIZE*sizeof(uint16_t),
			PROT_READ | PROT_WRITE,
			MAP_SHARED, F_screen, 0);
	if(Screen == MAP_FAILED) {
		fprintf(stderr, "Cannot map screen error %d\n", errno);
		exit(-2);
	}
}

void print_image() {
	printf("Printing an image to the screen\n");
	print_sprite(snake, OFFSET_X, OFFSET_Y);
}
#define IMG(x,y) image[x+IMG_X*y]
void print_sprite(const uint16_t *image,
		uint16_t off_x, uint16_t off_y) {
	uint16_t i, j;
	struct fb_copyarea rect;
	for(i=0; i<IMG_X; i++) {
		for(j=0; j<IMG_Y; j++) {
			if(IMG(i, j) != 0xffff)
				Screen[(i+off_x) + (j+off_y)*SCREEN_X] = IMG(i, j);
		}
	}
	rect.dx = off_x;
	rect.dy = off_y;
	rect.width = IMG_X;
	rect.height = IMG_Y;
	ioctl(F_screen, 0x4680, &rect);
}

#define BOARD(x,y) gameboard[x+y]
void print_gameboard(const uint16_t *gameboard){
    uint16_t i, j;
    struct fb_copyarea rect;

    for(i=0; i< SCREEN_X; i++){
        for(j=0; j < SCREEN_Y; j++){
            Screen[i + (j*SCREEN_X)] = color(BOARD(i,j));
        }
    }

    rect.dx = 0;
    rect.dy = 0;
    rect.width = SCREEN_X;
    rect.height = SCREEN_Y;

    ioctl(F_screen, 0x4680, &rect);
}

uint16_t color(uint16_t tileState){
    if(tileState == 0){
        return 0xffff;
    }else if (tileState == 1 || 2){
        return 0x0000;
    }
}

void screen_cleanup() {
	munmap(Screen, SCREEN_SIZE*sizeof(uint16_t));
	close(F_screen);
}
