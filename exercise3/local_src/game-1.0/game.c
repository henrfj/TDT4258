#include "game.h"

int main(int argc, char *argv[])
{
	screen_init();
	//print_image(); //just test
	//print_test_board(); //just test

	//test_gamepad_input();
	game_loop();
	screen_cleanup();
	return 0;
}

void game_loop(){

	/*Determine reoccuring game variables*/
	//TODO: can change the sizes of the variables, to not waste so much
	// same goes for global variables in the h file.
	uint8_t alive;
	uint16_t headPos[2];
	uint8_t direction;
	uint8_t grow;	//If it moves, new tail, if it grown, keep tail

	/*Main loop, which is used to reset the game */
	while(1){
		//clear BOARD, set alive
		//clears the BOARD
		memset(BOARD, 0, sizeof(uint16_t)*BOARD_SIZE*BOARD_SIZE);
		headPos[0] = 15;
		headPos[1] = 15;

		//Hardcode initial snakebody, draws on the board.
		initialize_snake(headPos);

		//Spawns a single initial fruit
		spawn_fruit();

		alive = 1;
		direction = RIGHT;
		
		/*Gameloop, which runs until the snake is dead */
		while(alive){

			/* Checks if direction has changed, and if so, changes direction*/
			direction = snake_direction(direction);
			/* Moves the snake in the current direction*/
			snake_movement(headPos, direction);
			/*checks if the new snake head position grows the snake or kills it.  */
			grow = FALSE;

			//snake eats fruit
			if(BOARD[headPos[0]][headPos[1]] == 2){ 
				grow=TRUE;
				//TODO: play eating sound here
				spawn_fruit(); //Spawn a new fruit

			//snake crashes into itself (checks if the future head position is on a body part that is the tail)
			}else if (BOARD[headPos[0]][headPos[1]] == 1 &&
			!(headPos[0] == SNAKE_BODY[TAIL_INDEX][0] && headPos[1] == SNAKE_BODY[TAIL_INDEX][1] )) 
			{
				alive = 0;

			//Snake moves over board - currently treat is as dead
			}else if (headPos[0] > BOARD_SIZE-1 || headPos[0] < 0 || headPos[0] >= BOARD_SIZE-1 || headPos[0] < 0){
				
				alive=0;
			}
			reorder_snake(headPos, grow);
			//TODO: Call function to update the board. Clear + push board
			print_gameboard(BOARD);
			usleep(50);				//Framerate
		}
		
		/*the user is dead, requires a keypress to restart the game */
		while(alive == 0){
			if (get_input() != 0){
				alive = 1;
			}
		}
	}

}

/*
keeps track of all the snake body positions. Elements in snakebody are index shifted by 1. The new head is placed at index 0,
and TAIL_INDEX is increased if grow is true, causing the the original tail to not be removed.
*/
void reorder_snake(uint8_t head[], uint8_t grow){
	
	uint16_t counter = 0;	//current index to be shifted
	uint8_t storedShift[2]; //used to shift the value
	storedShift[0] = SNAKE_BODY[0][0];
	storedShift[1] = SNAKE_BODY[0][1];

	uint8_t temp[2];
	while(counter <= TAIL_INDEX){
		//
		temp[0] = SNAKE_BODY[counter+1][0];
		temp[1] = SNAKE_BODY[counter+1][1];
		//
		SNAKE_BODY[counter+1][0] = storedShift[0];
		SNAKE_BODY[counter+1][1] = storedShift[1];
		//
		storedShift[0] = temp[0];
		storedShift[1] = temp[1];
		//
		counter++;
	}
	if(grow){
		//snake ate fruit, increase tail index to keep the tail after the shift.
		TAIL_INDEX++;
	}else{
		//snake did not eat fruit, wipe the old tail
		BOARD[SNAKE_BODY[TAIL_INDEX+1][0]][SNAKE_BODY[TAIL_INDEX+1][1]] = 0;
		

	}

	//adds new snake head to the BOARD
	SNAKE_BODY[0][0] = head[0];
	SNAKE_BODY[0][1] = head[1];
	BOARD[head[0]][head[1]] = 1;

}


uint8_t get_input(){
	uint8_t button_value = read_button_value();

	/* Always reference with the left gamepad */
	if (CHECK_BTN(button_value, LEFT)) {
		return LEFT;
	} else if (CHECK_BTN(button_value, UPL)) {
		return UPL;
	} else if (CHECK_BTN(button_value, RIGHTL)) {
		return RIGHT;
	} else if (CHECK_BTN(button_value, DOWNL)) {
		return DOWNL;
	} else if (CHECK_BTN(button_value, LEFTR)) {
		return LEFT;
	} else if (CHECK_BTN(button_value, UPR)) {
		return UPL;
	} else if (CHECK_BTN(button_value, RIGHT)) {
		return RIGHT;
	} else if (CHECK_BTN(button_value, DOWNR)) {
		return DOWNL;
	}else{
		return 0;
	}
}

uint8_t snake_direction(uint8_t direction){

	//Get a new directional input from the gamepad	
	uint8_t newDirection = get_input();

	//Checks if it is a leagal move, can only move 90 degree, not 180
	if (newDirection == 0){
		//No change
		return direction;
	} else if ((newDirection==LEFT && direction==RIGHT) ||
	 (newDirection==RIGHT && direction==LEFT)){
		//No change
		return direction;
	}else if((newDirection==UPL && direction==DOWNL) ||
	 (newDirection==DOWNL && direction==UPL)){
		//No change
		return direction;

	}
	//Change as it is a legal move
	return newDirection;
}

/*Sets new snakeHEAD postition, based on direction */
void snake_movement(uint8_t headPos[2], uint8_t direction){
	//calibrated to give the correct result on the screen.
	if(direction==LEFT){
		headPos[1]--;
	}else if (direction == RIGHT){
		headPos[1]++;
	}else if(direction == UPL){
		headPos[0]--;
	}else if(direction == DOWNL){
		headPos[0]++;
	}
}


/*
	Spawns a single fruit at a random location on the BOARD.
	Only spawns fruit in a free spot. 
	Finds a random x and y position on the BOARD, and draws a 2 = a fruit
*/
int spawn_fruit(){
	

	/* 
	Setting upper and lower bound of the rand-function.
	This will be indexes, so subracting one from board size
	*/
	uint8_t upper = BOARD_SIZE - 1;
	uint8_t lower = 0;

	//Seeding the rand function.
	srand(time(0));
	uint8_t x_pos, y_pos;
	x_pos = (rand() % (upper - lower + 1)) + lower; 
	y_pos = (rand() % (upper - lower + 1)) + lower; 
	
	if  (BOARD[x_pos][y_pos] == 0){
		//adds the fruit to the board (2 represent fruit)
		BOARD[x_pos][y_pos] = 2;
		return 1;

	}else{
		// Calls itself until it finds a suitable spot for a fruit
		return spawn_fruit();
	}


}


/*
	Hardcode the new snakebody onto the board.
	Uses headposition, and draws a three-sized snake.
*/
void initialize_snake(uint8_t headPos[2]){
	
	//Initialize head
	SNAKE_BODY[0][0] = headPos[0];
	SNAKE_BODY[0][1] = headPos[1];

	BOARD[SNAKE_BODY[0][0]][SNAKE_BODY[0][1]] = 1;

	//Initialize Middle
	SNAKE_BODY[1][0] = headPos[0]-1;
	SNAKE_BODY[1][1] = headPos[1];

	BOARD[SNAKE_BODY[1][0]][SNAKE_BODY[1][1]] = 1;

	//Initialize Head
	SNAKE_BODY[2][0] = headPos[0] - 2;
	SNAKE_BODY[2][1] = headPos[1];

	BOARD[SNAKE_BODY[2][0]][SNAKE_BODY[2][1]] = 1;
	TAIL_INDEX = 2;
}

/**
 * Testfunction for printing the board as a string
*/
void print_board(){
	uint16_t i, j;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			printf("%d", BOARD[i][j]);
		}
	}
}
