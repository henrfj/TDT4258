#include "screen_engine.h"
#include "foo.h"

void print_image() {
	uint16_t i, j;
	uint16_t *screen;
	int f_screen = open("/dev/fb0", O_RDWR);
	if(f_screen < 0) {
		fprintf(stderr, "Cannot open screen\n");
		exit(-1);
	}
	screen = mmap(NULL, SCREEN_SIZE*sizeof(uint16_t),
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, f_screen, 0);
	if(screen == MAP_FAILED) {
		fprintf(stderr, "Cannot map screen error %s\n", strerror(errno));
		return;
	}
	printf("Printing an image to the screen\n");
	for(i=0; i<IMG_X; i++) {
		for(j=0; j<IMG_X; j++) {
			screen[i + j*SCREEN_Y] = peach[i][j];
			//if(write(f_screen, peach[i], IMG_X*sizeof(uint16_t)) <
			//		IMG_X * sizeof(uint16_t))
			//	printf("Wrong write..\n");
		}
	}
	struct fb_copyarea rect;
	rect.dx = 0;
	rect.dy = 0;
	rect.width = SCREEN_X;
	rect.height = SCREEN_Y;
	ioctl(f_screen, 0x4680, &rect);

	munmap(screen, SCREEN_SIZE*sizeof(uint16_t));
	close(f_screen);
}
