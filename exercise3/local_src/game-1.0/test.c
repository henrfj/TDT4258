#include "test.h"


int test_gamepad_input(){
	printf("Hello World, I'm test!\n");

	FILE* gamepad;
	char button_value;
	while(1){
		gamepad = fopen("/dev/gamepad", "r");
		if (!gamepad){
			printf("gamepad not existing");
			exit(-1);
		}
		fread(&button_value, sizeof(char), 1, gamepad);
		printf("Value: %x\n", button_value);

		fclose(gamepad);
		usleep(50000);
	}
	exit(EXIT_SUCCESS);
}


void test_spawn_fruit(){
	//Spawn three fruits
	printf("Spawning three fruits and printing the board\n");
	BOARD = {0}{0};
	spawn_fruit();
	spawn_fruit();
	spawn_fruit();
	
	print_board();
}


void test_initialize_snake(){
	printf("initialize Snake and printing board\n")
	BOARD = {0}{0};
	int headPos[2] = [15, 15];
	initialize_snake(headPos);
	print_board();
}


void test_reorder_snake(){
	printf("First: initialize a snake")
	int head[2] = [15, 15];
	BOARD = {0}{0};
	initialize_snake(head);
	printf("Second: move snake DOWNL")
	snake_movement(head, DOWNL);
	printf("Third: reorder snake, print board")
	reorder_snake(head, FALSE);
	print_board();
}


void test_snake_movement(){
	// DOWNL
	BOARD = {0}{0};
	int headPos[2] = [15, 15];
	printf("Old headPos:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, DOWNL)
	printf("New headPos, after moving DOWNL:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}
	// UPL
	BOARD = {0}{0};
	headPos[2] = [15, 15];
	printf("Old headPos:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, UPL)
	printf("New headPos, after moving UPL:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}
	// RIGHT
	BOARD = {0}{0};
	headPos[2] = [15, 15];
	printf("Old headPos:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, RIGHT)
	printf("New headPos, after moving RIGHT:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}
	//LEFT 
	BOARD = {0}{0};
	headPos[2] = [15, 15];
	printf("Old headPos:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, LEFT)
	printf("New headPos, after moving LEFT:\n")
	for(int i = 0; i<2; i++){
		printf("%d:", i)
		printf("%d\n" , headPos[i]);
	}

}



