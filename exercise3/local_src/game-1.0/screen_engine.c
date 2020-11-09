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
			MAP_SHARED, f_screen, 0);
	if(screen == MAP_FAILED) {
		fprintf(stderr, "Cannot map screen error %d\n", errno);
		return;
	}
	printf("Printing an image to the screen\n");
	for(i=0; i<IMG_X; i++) {
		for(j=0; j<IMG_Y; j++) {
			if(snake_jpg[i][j] != 0xffff)
				screen[(i+OFFSET_X) + (j+OFFSET_Y)*SCREEN_X] = snake_jpg[i][j];
		}
	}
	struct fb_copyarea rect;
	rect.dx = OFFSET_X;
	rect.dy = OFFSET_Y;
	rect.width = IMG_X;
	rect.height = IMG_Y;
	ioctl(f_screen, 0x4680, &rect);

	munmap(screen, SCREEN_SIZE*sizeof(uint16_t));
	close(f_screen);
}
