#include "test.h"


int test_gamepad_input(){
	printf("Hello World, I'm test!\n");

	char button_value;
	while(1){
		button_value = get_input();
		printf("Value: %x\n", button_value);

		usleep(50000);
	}
	exit(EXIT_SUCCESS);
}


void test_spawn_fruit(){
	//Spawn three fruits
	printf("Spawning three fruits and printing the board\n");
	//BOARD = {0}{0};
	memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	spawn_fruit();
	spawn_fruit();
	spawn_fruit();
	
	print_board();
}


void test_initialize_snake(){
	printf("initialize Snake and printing board\n");
	//BOARD = {0}{0};
	memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	int headPos[] = {15, 15};
	initialize_snake(headPos);
	print_board();
}


void test_reorder_snake(){
	printf("First: initialize a snake");
	int head[2] = {15, 15};
	//BOARD = {0}{0};
	memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	initialize_snake(head);
	printf("Second: move snake DOWNL");
	snake_movement(head, DOWNL);
	printf("Third: reorder snake, print board");
	reorder_snake(head, FALSE);
	print_board();
}


void test_snake_movement(){
	// DOWNL
	int8_t i;
	memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	int headPos[2] = {15, 15};
	printf("Old headPos:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, DOWNL);
	printf("New headPos, after moving DOWNL:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}
	// UPL
	memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	headPos[0] = 15;
	headPos[1] =15;
	printf("Old headPos:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, UPL);
	printf("New headPos, after moving UPL:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}
	// RIGHT
	memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	headPos[0] = 15;
	headPos[1] =15;
	printf("Old headPos:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, RIGHT);
	printf("New headPos, after moving RIGHT:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}
	//LEFT 
	
	memset(BOARD, 0, sizeof(int)*BOARD_SIZE*BOARD_SIZE);
	headPos[0] = 15;
	headPos[1] =15;
	printf("Old headPos:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}
	snake_movement(headPos, LEFT);
	printf("New headPos, after moving LEFT:\n");
	for(i = 0; i<2; i++){
		printf("%d:", i);
		printf("%d\n" , headPos[i]);
	}

}



