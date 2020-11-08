#include "gamepad_engine.h"



char read_button_value(){
    FILE* gamepad;
	char button_value;
    gamepad = fopen("/dev/gamepad", "r");
    if (!gamepad){
        printf("gamepad not existing");
        exit(-1);
    }
    fread(&button_value, sizeof(char), 1, gamepad);
    //printf("Value: %x\n", button_value);

    fclose(gamepad);

    return button_value;
}

void gamepad_test() {
	char value = read_button_value();
	if(CHECK_BTN(value, LEFT))
		printf("LEFT\n");
	if(CHECK_BTN(value, RIGHT))
		printf("RIGHT\n");
}
