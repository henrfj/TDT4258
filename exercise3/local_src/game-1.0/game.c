#include "game.h"

int main(int argc, char *argv[])
{
	#testy();
	game_loop();
	return 0;
}

void gameloop(){
	int inputs;
	while(1){
		inputs = run_gamepad_engine();
		
		/*
		TODO: game logic. Produce a new frame based on gamepad inputs.
		Play sound to mach situation.
		Pass on to screen engine and sound engine. 
		*/
		
		run_sound_engine();
		run_screen_engine();
		sleep(1);
	}

}
