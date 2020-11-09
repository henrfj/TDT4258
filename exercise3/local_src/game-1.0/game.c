#include "game.h"

int main(int argc, char *argv[])
{
	game_loop();
	return 0;
}

void game_loop(){
	while(1){
		/*
		TODO: game logic. Produce a new frame based on gamepad inputs.
		Play sound to mach situation.
		Pass on to screen engine and sound engine. 
		*/
		//run_gamepad_engine();
		print_image();
		run_game_logics(); 		//Update gamestate
		//run_sound_engine();		//Play sound based on gamestate
		//run_screen_engine();	//Update screen based on gamestate
		sleep(1);				//Framerate
	}

}

void run_game_logics(){
	uint8_t button_value = read_button_value();
	if (CHECK_BTN(button_value, LEFT)) {
		// Do something
	} else if (CHECK_BTN(button_value, UPL)) {
		// Do something
	} else if (CHECK_BTN(button_value, RIGHTL)) {
		// Do something
	} else if (CHECK_BTN(button_value, DOWNL)) {
		// Do something
	} else if (CHECK_BTN(button_value, LEFTR)) {
		// Do something
	} else if (CHECK_BTN(button_value, UPR)) {
		// Do something
	} else if (CHECK_BTN(button_value, RIGHT)) {
		// Do something
	} else if (CHECK_BTN(button_value, DOWNR)) {
		// Do something
	}
}
