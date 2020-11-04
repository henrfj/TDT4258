#include "game.h"

int main(int argc, char *argv[])
{
	#testy();
	game_loop();
	return 0;
}

void game_loop(){
	char button_value;
	while(1){
		/*
		TODO: game logic. Produce a new frame based on gamepad inputs.
		Play sound to mach situation.
		Pass on to screen engine and sound engine. 
		*/
		run_gamepad_engine();
		run_game_logics(); 		//Update gamestate
		run_sound_engine();		//Play sound based on gamestate
		run_screen_engine();	//Update screen based on gamestate
		sleep(1);				//Framerate
	}

}

void run_game_logics(){
	button_value = read_button_value();
	if (button_value == LEFT) {
		// Do something
	} else if (button_value == UPL) {
		// Do something
	} else if (button_value == RIGHTL) {
		// Do something
	} else if (button_value == DOWNL) {
		// Do something
	} else if (button_value == LEFTR) {
		// Do something
	} else if (button_value == UPR) {
		// Do something
	} else if (button_value == RIGHT) {
		// Do something
	} else if (button_value == DOWNR) {
		// Do something
	}
}
