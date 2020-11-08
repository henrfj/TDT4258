#include "game.h"

int main(int argc, char *argv[])
{
	game_loop();
	return 0;
}

void game_loop(){

	/*Determine reoccuring game variables*/
	int board [BOARD_SIZE][BOARD_SIZE]
	int alive;
	int headPos[2];
	int fruitPos[2];
	int direction;
	int newDirection;
	int snakeBody[2][0] //keeps track of the snake - might be switched with a queue if there exists one

	while(1){
		//clear board, set alive

		//TODO: clear board (use 0s for empty, 1 for snake and 2 for fruit)
		int alive = 1;
		headPos = [15, 15]
		direction = RIGHT;
		int keepTail; //for reorder_snake() solution, should be removed if not used
		// fruitPos == generateFruit()
		while(alive){
			/* Checks if direction has changed, and if so, changes direction*/

			/* TODO - make logic so you cant go from left to right!*/ 
			newDirection = getInput()
			if (newDirection =! 0){
				direction = newDirection
			}
			
			/*Sets new snakeHEAD */
			if(direction==LEFT){
				headPos[0]--; 
			}else if (direction == RIGHT){
				headPos[0]++;
			}else if(direction == UP){
				headPos[1]++;
			}else if(direction == down){
				headPos[1]--;
			}

			/*checks the new snake heads position */
			if(headPos[0] == fruitPos[0] && headPos[1] == fruitPos[1] ){
				board[headPos[0]][headPos[1]] == 1; // adds the new snake head to the board(hence increasing the snake)
				keepTail=true;
				//TODO: play eating sound here
				//TODO: fruitPos == generateFruit()
			}else if (board[headPos[0]][headPos[1]] == 1){
				alive = 0;
				keepTail=false;
				//TODO: play dead sound here
			}else if ([headPos[0] > BOARD_SIZE || headPos[0] < 0 || headPos[0] > BOARD_SIZE || headPos[0] < 0)
				alive=0;
				keepTail=false
				
				//snake dies?
				//TODO: play dead sound here
			}else
				//TODO: remove end of snake! Ups, we need to know the position,and be able to update it!
				//Do we need a new datastructure? How about a linked list, going from snake end to head?
				//posible solution 
			}
			//reorder_snake(&head, &snakeBody, &gameBoard, keepTail)
			
			

			//run_gamepad_engine();
			//run_sound_engine();	//Play sound based on gamestate
			//run_screen_engine();	//Update screen based on gamestate
			sleep(1);				//Framerate
		}
		/*the user is dead, requires a keypress to restart the game */
		while(!alive){
			if (get_input() != 0){
				alive = 1;
			}
		}
	}

}

//hacky solution, requires o(n) iterations where n is snake length for each game tick.
void reorder_snake(int[] *head, int[][] *snakeBody, int [][] *gameBoard, int keepTail){
	/*shift all elements index by one,
	remove the last element if keepTail is true
	set index 0 to head.
	set 0 at gameboard position of the tail.*/
}

void get_input(){
	uint8_t button_value = read_button_value();
	if (CHECK_BTN(button_value, LEFT)) {
		return LEFT
	} else if (CHECK_BTN(button_value, UPL)) {
		return UP
	} else if (CHECK_BTN(button_value, RIGHTL)) {
		return RIGHT
	} else if (CHECK_BTN(button_value, DOWNL)) {
		return DOWN
	} else if (CHECK_BTN(button_value, LEFTR)) {
		return LEFT
	} else if (CHECK_BTN(button_value, UPR)) {
		return UP
	} else if (CHECK_BTN(button_value, RIGHT)) {
		return RIGHT
	} else if (CHECK_BTN(button_value, DOWNR)) {
		return DOWN
	}else{
		//assume that this would be returned if no buttons are pressed? (right, Gabriele?)
		return 0;
	}
}
