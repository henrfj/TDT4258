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
	uint8_t keepTail;	//If it moves, new tail, if it grown, keep tail

	while(1){
		//clear BOARD, set alive
		//clears the BOARD
		BOARD = {0}{0};
		headPos = [15, 15];

		//Hardcode initial snakebody, draws on the board.
		initialize_snake(headPos);
		
		
		int alive = 1;
		direction = RIGHT;
		//for reorder_snake() solution, should be removed if not used
		//Spawns a single initial fruit
		spawn_fruit();
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
				BOARD[headPos[0]][headPos[1]] == 1; // adds the new snake head to the BOARD(hence increasing the snake)
				keepTail=true;
				//TODO: play eating sound here
				spawn_fruit(); //Spawn a new fruit

			//snake crashes into itself
			}else if (BOARD[headPos[0]][headPos[1]] == 1){
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

//keeps track of all the snake body positions. snakebody is index shifted by 1, new head is placed at 0,
// and TAIL_INDEX is increased if keepTail is true(simulating eating)
void reorder_snake(int head[], int keepTail){
	
	int counter = 0;	//current index to be shifted
	int storedShift[2]; //used to shift the value
	while(counter <= TAIL_INDEX){
		storedShift = SNAKE_BODY[count+1];
		SNAKE_BODY[counter+1] = SNAKE_BODY[counter];
		counter++;
	}
	if(keepTail){
		//increase snakeLength
		TAIL_INDEX++;
	}else{
		//snake did not eat fruit, wipe old tail
		BOARD[SNAKE_BODY[TAIL_INDEX][0]]SNAKE_BODY[TAIL_INDEX][1]] = 0;
		//SNAKE_BODY[TAIL_INDEX+1] = {-1};  unneccessary, as TAIL_INDEX makes all data beyond unused.

	}
	//adds new snake head to the BOARD
	BOARD[*head[0]][*head[1]] = 1;

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
	/*Spawns a single fruit at a random location on the BOARD.
	Only spawns fruit in a free spot. 
	Finds a random x and y position on the BOARD, and draws a 2 = a fruit
	*/
	int upper = BOARD_SIZE - 1;
	int lower = 0;

	//Seeding the rng
	srand(time(0));
	int x_pos, int y_pos;
	x_pos = (rand() % (upper - lower + 1)) + lower; 
	y_pos = (rand() % (upper - lower + 1)) + lower; 
	
	if  (BOARD[x_pos][y_pos] == 0){
		BOARD[x_pos][y_pos] = 2;
	}
	else
	{
		// Calls itself until it finds a suitable spot for a fruit
		spawn_fruit();
	}


}

void initialize_snake(int headPos[]){}
	/*
	Hardcode the new snakebody onto the board.
	*/

	//Head
	SNAKE_BODY[0] = headPos;
	BOARD[snakeBody[0][0]][SNAKE_BODY[0][1]] = 1;

	//Middle
	SNAKE_BODY[1] = [headPos[0] - 1, headPos[1]];
	BOARD[SNAKE_BODY[1][0]][SNAKE_BODY[1][1]] = 1;

	//Tail
	SNAKE_BODY[2] = [headPos[0] - 2, headPos[1]];
	BOARD[SNAKE_BODY[2][0]][SNAKE_BODY[2][1]] = 1;
	TAIL_INDEX = 2;
}
