#include "game.h"

int main(int argc, char *argv[])
{
	screen_init();
	game_loop();
	screen_cleanup();
	return 0;
}

void game_loop(){

	/*Reoccuring game variables */

	uint8_t alive; 		//determins if the snake is alive or not
	int8_t headPos[2];//position of the snake head
	uint8_t direction;  //The direction of the snake
	uint8_t grow;		//Determins if the snake grows or not

	/*Main loop, which is used to reset the game */
	while(1){
		
		//clears board
		memset(BOARD, 0, sizeof(uint16_t)*BOARD_SIZE*BOARD_SIZE);

		//resets head position and direction
		headPos[0] = 15;
		headPos[1] = 15;
		direction = RIGHT;

		//intialize the snake body and drawis it to the board
		initialize_snake(headPos);

		//Spawns an initial fruit
		spawn_fruit();

		//enables the alive loop
		alive = 1;
		
		
		/*Game loop, which runs until the snake is dead */
		while(alive){

			/* Checks if direction has changed, and if so, changes direction*/
			direction = snake_direction(direction);
			
			/* Moves the snake in the current direction*/
			snake_movement(headPos, direction);
			
			grow = FALSE;


			/*checks if the new snake head position grows the snake or kills it.  */

			//Snake moves over board - currently treat is as dead
			if (headPos[0] >= BOARD_SIZE || headPos[0] < 0 || headPos[1] >= BOARD_SIZE || headPos[1] < 0){
				alive=0;
			//snake crashes into itself (checks if the future head position is on a body part that is the tail)
			}else if (BOARD[headPos[0]][headPos[1]] == 1 &&
			!(headPos[0] == SNAKE_BODY[TAIL_INDEX][0] && headPos[1] == SNAKE_BODY[TAIL_INDEX][1] )) 
			{
				alive = 0;

			//Snakehead is at a fruit position
			}else if(BOARD[headPos[0]][headPos[1]] == 2){ 
				grow=TRUE;
				spawn_fruit(); 
			}

			//perform the move
			reorder_snake(headPos, grow);

		
			//draws the graphical board (there it's a linear array..)
			print_gameboard((uint16_t *)BOARD);

			//Framerate
			usleep(20);
		}
		
		/*Game loop for when the snake is dead, waits for input to restart.*/
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
void reorder_snake(int8_t head[], uint8_t grow){
	
	uint16_t counter = 0;	//current index to be shifted
	int8_t storedShift[2]; //used to shift the value
	storedShift[0] = SNAKE_BODY[0][0];
	storedShift[1] = SNAKE_BODY[0][1];

	int8_t temp[2];
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
		//Snake ate fruit -> increase tail index to keep the tail after the shift.
		TAIL_INDEX++;
	}else{
		//Snake did not eat fruit -> clear the old tail
		BOARD[SNAKE_BODY[TAIL_INDEX+1][0]][SNAKE_BODY[TAIL_INDEX+1][1]] = 0;

	}
	//adds new snake head to the BOARD
	SNAKE_BODY[0][0] = head[0];
	SNAKE_BODY[0][1] = head[1];
	BOARD[head[0]][head[1]] = 1;

}

/*Fetches the input from the button*/
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

/*Fetches new directin based on buttoninput and past direction*/
uint8_t snake_direction(uint8_t direction){

	//Get a new directional input from the gamepad	
	uint8_t newDirection = get_input();

	//Checks if it is a leagal move, can only move 90 degree, not 180
	if (newDirection == 0){
		// Illegal move -> no change
		return direction;
	} else if ((newDirection==LEFT && direction==RIGHT) ||
	 (newDirection==RIGHT && direction==LEFT)){
		// Illegal move -> no change
		return direction;
	}else if((newDirection==UPL && direction==DOWNL) ||
	 (newDirection==DOWNL && direction==UPL)){
		// Illegal move -> no change
		return direction;

	}
	//Change as it is a legal move
	return newDirection;
}

/*Sets new head postition, based on direction */
void snake_movement(int8_t headPos[2], uint8_t direction){
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
void initialize_snake(int8_t headPos[2]){
	
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
