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
	int alive;
	int headPos[2];
	int direction;
	int grow;	//If it moves, new tail, if it grown, keep tail

	while(1){
		//clear BOARD, set alive
		//clears the BOARD
		//BOARD = {0}{0};
		memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
		headPos[0] = 15;
		headPos[1] = 15;

		//Hardcode initial snakebody, draws on the board.
		initialize_snake(headPos);
		//Spawns a single initial fruit
		spawn_fruit();

		alive = 1;
		direction = RIGHT;
		//for reorder_snake() solution, should be removed if not used
		
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

			//snake crashes into itself
			}else if (BOARD[headPos[0]][headPos[1]] == 1 &&
			!(headPos[0] == SNAKE_BODY[TAIL_INDEX][0] && headPos[1] == SNAKE_BODY[TAIL_INDEX][1] )) //checks if the future head position is not the tail
			{
				alive = 0;
				
				//TODO: play dead sound here

			//Snake moves over board - currently treat is as dead
			}else if (headPos[0] >= BOARD_SIZE || headPos[0] < 0 || headPos[1] >= BOARD_SIZE || headPos[1] < 0){
				alive=0;
				//TODO: play dead sound here
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

//keeps track of all the snake body positions. snakebody is index shifted by 1, new head is placed at 0,
// and TAIL_INDEX is increased if grow is true(simulating eating)
void reorder_snake(int head[], int grow){
	
	int counter = 0;	//current index to be shifted
	int storedShift[2]; //used to shift the value
	storedShift[0] = SNAKE_BODY[0][0];
	storedShift[1] = SNAKE_BODY[0][1];

	int temp[2];
	while(counter <= TAIL_INDEX){
		//lagre count +1
		//sette count +1 til verdien av count
		//sette verdien til st
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
		//SNAKE_BODY[TAIL_INDEX+1] = {-1};  unneccessary, as TAIL_INDEX makes all data beyond unused.

	}
	//adds new snake head to the BOARD
	SNAKE_BODY[0][0] = head[0];
	SNAKE_BODY[0][1] = head[1];
	BOARD[head[0]][head[1]] = 1;

}


int get_input(){
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
		//assume that this would be returned if no buttons are pressed? (right, Gabriele?)
		return 0;
	}
}

int snake_direction(int direction){

	//Get a new directional input from the gamepad	
	int newDirection = get_input();

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

void snake_movement(int headPos[2], int direction){
	/*Sets new snakeHEAD postition, based on direction */
	if(direction==LEFT){
		//headPos[0]--;
		headPos[1]--;
	}else if (direction == RIGHT){
		//headPos[0]++;
		headPos[1]++;
	}else if(direction == UPL){
		//headPos[1]++;
		headPos[0]--;
	}else if(direction == DOWNL){
		//headPos[1]--;
		headPos[0]++;
	}
}

int spawn_fruit(){
	/*
	Spawns a single fruit at a random location on the BOARD.
	Only spawns fruit in a free spot. 
	Finds a random x and y position on the BOARD, and draws a 2 = a fruit
	*/

	/* 
	Setting upper and lower bound of the rand-function.
	This will be indexes, so subracting one from board size
	*/
	int upper = BOARD_SIZE - 1;
	int lower = 0;

	//Seeding the rand function.
	srand(time(0));
	int x_pos, y_pos;
	x_pos = (rand() % (upper - lower + 1)) + lower; 
	y_pos = (rand() % (upper - lower + 1)) + lower; 
	
	if  (BOARD[x_pos][y_pos] == 0){
		//Fruits are represented as a 2 on the board
		BOARD[x_pos][y_pos] = 2;
		return 1;

	}else{
		// Calls itself until it finds a suitable spot for a fruit
		return spawn_fruit();
	}


}

void initialize_snake(int headPos[2]){
	/*
	Hardcode the new snakebody onto the board.
	Uses headposition, and draws a three-sized snake.
	*/

	//Head
	SNAKE_BODY[0][0] = headPos[0];
	SNAKE_BODY[0][1] = headPos[1];

	BOARD[SNAKE_BODY[0][0]][SNAKE_BODY[0][1]] = 1;

	//Middle
	SNAKE_BODY[1][0] = headPos[0]-1;
	SNAKE_BODY[1][1] = headPos[1];

	BOARD[SNAKE_BODY[1][0]][SNAKE_BODY[1][1]] = 1;

	//Tail
	SNAKE_BODY[2][0] = headPos[0] - 2;
	SNAKE_BODY[2][1] = headPos[1];
	BOARD[SNAKE_BODY[2][0]][SNAKE_BODY[2][1]] = 1;
	TAIL_INDEX = 2;
}

void print_board(){
	uint16_t i, j;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			printf("%d", BOARD[i][j]);
		}
	}
}
