#include "screen_engine.h"
#include "sprites.h"

static int F_screen;
static uint16_t *Screen;
#define SCREEN(x, y) Screen[(x) + SCREEN_X*(y)]

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
	memset(Screen, 0, SCREEN_SIZE*sizeof(uint16_t));
	screen_update(0, 0, SCREEN_X, SCREEN_Y);
}

void screen_update(uint16_t x, uint16_t y,
		uint16_t width, uint16_t height) {
	struct fb_copyarea rect;
	rect.dx = x;
	rect.dy = y;
	rect.width = width;
	rect.height = height;
	ioctl(F_screen, 0x4680, &rect);
}	

void print_image() {
	printf("Printing an image to the screen\n");
	print_sprite(head, 0, 60);
	print_sprite(tail, 60, 60);
	print_sprite(snake, 60, 0);
}
#define IMG_SIZE 12
#define IMG(x,y) image[x+IMG_SIZE*y] //FIXME
void print_sprite(const uint16_t *image,
		uint16_t off_x, uint16_t off_y) {
	uint16_t i, j;
	for(i=0; i<IMG_SIZE; i++) {
		for(j=0; j<IMG_SIZE; j++) {
			if(IMG(i, j) != 0xffff)
				SCREEN(i+off_x, j+off_y) = IMG(i, j);
		}
	}
	//screen_update(off_x, off_y, IMG_SIZE, IMG_SIZE);
}

//x and y are in screen size
#define BOARD(x,y) gameboard[(x/BOARD_RATIO)+(y/BOARD_RATIO)*BOARD_SIDE]
void print_gameboard(const uint16_t *gameboard){
    uint16_t i, j;

    for(i=0; i< SCREEN_X; i++){
		for(j=0; j < SCREEN_Y; j++){
			if(i>BOARD_SCREEN) {
				SCREEN(i, j) = PAD_COLOR;
			} else {
				//SCREEN(i, j) = color(BOARD(i,j));
				color_tile(gameboard, i, j);
			}
		}
    }
	screen_update(0, 0, SCREEN_X, SCREEN_Y);
}
void print_test_board() {
	uint16_t board[BOARD_SIDE*BOARD_SIDE] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,
		0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,5,0,
		0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0
	};
	print_gameboard(board);
}

uint16_t color(uint16_t tileState){
    if(tileState == 0){
        return 0xffff;
    }else if (tileState == 1 || tileState == 2){
        return 0x0000;
    }
	return PAD_COLOR;
}
void color_tile(uint16_t *gameboard, uint8_t x, uint8_t y){
	uint16_t tileState = BOARD(x,y);
    if(tileState == 0){
        SCREEN(x, y) = BG_COLOR;
    } else if (tileState == 1 || tileState == 2){
        SCREEN(x, y) = SNK_COLOR;
    } else if(x % BOARD_RATIO == 0 && y % BOARD_RATIO == 0) {
		//here print sprites
		if(tileState == 3) {
			print_sprite(tail, x, y);
		}
		if(tileState == 4) {
			print_sprite(head, x, y);
		}
		if(tileState == 5) {
			print_sprite(apple, x, y);
		}
	}
}

void screen_cleanup() {
	munmap(Screen, SCREEN_SIZE*sizeof(uint16_t));
	close(F_screen);
}
