#include "test.h"


int testy(){
	printf("Hello World, I'm test!\n");

	FILE* gamepad;
	char button_value;
	while(1){
		gamepad = fopen("/dev/gamepad", "r");
		if (!gamepad){
			printf("gamepad not existing");
			exit(-1);
		}
		fread(&button_value, sizeof(char), 1, gamepad);
		printf("Value: %x\n", button_value);

		fclose(gamepad);
		usleep(50000);
	}
	exit(EXIT_SUCCESS);
}
