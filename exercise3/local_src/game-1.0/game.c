#include "game.h"

int main(int argc, char *argv[])
{
	game_loop();
	return 0;
}

void game_loop(){

	/*Determine reoccuring game variables*/
	int alive;
	int headPos[2];
	int fruitPos[2];
	int direction;
	int newDirection;
	int snakeBody[BOARD_SIZE*BOARD_SIZE][2] //keeps track of the snake - might be switched with a queue if there exists one

	while(1){
		//clear board, set alive
		//clears the board
		board = {0}{0};

		//TODO: hardcode initial snakebody
		
		int alive = 1;
		headPos = [15, 15]
		direction = RIGHT;
		int keepTail; //for reorder_snake() solution, should be removed if not used
		// fruitPos == generateFruit()
		while(alive){

			/* Checks if direction has changed, and if so, changes direction*/
			newDirection = getInput()
			if (newDirection =! 0){
				if((newDirection == LEFT && direction == RIGHT || newDirection == RIGHT && direction==LEFT) 
				||
				(newDirection == UPL && direction==DOWNL) || newDirection == DOWNL && direction==UPL))
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

			/*checks if the new snake head position grows the snake or kills it.  */
			keepTail = false;
		
			//snake eats fruit
			if(headPos[0] == fruitPos[0] && headPos[1] == fruitPos[1] ){ 
				keepTail=true;
				//TODO: play eating sound here
				//TODO: fruitPos == generateFruit()

			//snake crashes into itself
			}else if (board[headPos[0]][headPos[1]] == 1){
				//TODO: check if it hits tail
				alive = 0;
				
				//TODO: play dead sound here

			//Snake moves over board - currently treat is as dead
			}else if ([headPos[0] > BOARD_SIZE || headPos[0] < 0 || headPos[0] > BOARD_SIZE || headPos[0] < 0)
				alive=0;
				//TODO: play dead sound here
			}
			reorder_snake(&head, keepTail)
			
			

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
//TODO: add tailIndex, shift only when fruit i eaten(snake grows), otherwise skip
void reorder_snake(int head[], int keepTail){
	
	//snake ate a fruit, body needs to be shifted by one

	//needs to reorder anyway. fix!
	if(keepTail){
		int counter = 1;
		int storedShift[2]; //used to shift the value
		while(SNAKE_BODY[TAIL_INDEX][0] =! -1 ){
			storedShift = SNAKE_BODY[count+1]
			SNAKE_BODY[count+1] = SNAKE_BODY[count]
		}
	}else{
		//snake
		BOARD[SNAKE_BODY[counter][0]]SNAKE_BODY[counter][1]] = 0; //updates board
		SNAKE_BODY[TAIL_INDEX] = {-1} //might not work

	}
	//adds new snake head to the board
	BOARD[*head[0]][*head[1]] = 1

}


int get_input(){
	uint8_t button_value = read_button_value();

	/* Always reference with the left gamepad */
	if (CHECK_BTN(button_value, LEFT)) {
		return LEFT
	} else if (CHECK_BTN(button_value, UPL)) {
		return UPL
	} else if (CHECK_BTN(button_value, RIGHTL)) {
		return RIGHT
	} else if (CHECK_BTN(button_value, DOWNL)) {
		return DOWNL
	} else if (CHECK_BTN(button_value, LEFTR)) {
		return LEFT
	} else if (CHECK_BTN(button_value, UPR)) {
		return UPL
	} else if (CHECK_BTN(button_value, RIGHT)) {
		return RIGHT
	} else if (CHECK_BTN(button_value, DOWNR)) {
		return DOWNL
	}else{
		//assume that this would be returned if no buttons are pressed? (right, Gabriele?)
		return 0;
	}
}


void spawn_fruit(){
	/*Spawns a single fruit at a random location on the board.
	Only spawns fruit in a free spot. 
	Finds a random x and y position on the board, and draws a 2 = a fruit
	*/
	int upper = BOARD_SIZE - 1;
	int lower = 0;

	//Seeding the rng
	srand(time(0));
	int x_pos, int y_pos;
	x_pos = (rand() % (upper - lower + 1)) + lower; 
	y_pos = (rand() % (upper - lower + 1)) + lower; 
	
	if  (board[x_pos][y_pos] == 0){
		board[x_pos][y_pos] = 2;
	}
	else
	{
		// Calls itself until it finds a suitable spot for a fruit
		spawn_fruit();
	}


}
