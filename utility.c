/*
 * Lab 3 SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */


#include "utility.h"
#include <pthread.h>

#define RED "\x1b[0;31m"
#define RESET "\x1b[0m"

// print the current board 2d array (9 by 9)
void print_board(void) {
	// go through every element of board array
	for(int i = 0; i < 9; ++i) {
		for(int j = 0; j < 9; ++j) {
			// use escape sequences to output '0' in red
			if(board[i][j] == 0)
				printf(RED);
			else
				printf(RESET);

			// output the element
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}

	// escape sequence to reset terminal color
	printf(RESET);
}

// loads in the input file from filename, and saves it to the board 2d array
void load_board(char *file_name) {
	// TODO

	// currently inits to random number
	for(int i = 0; i < 9; ++i)
		for(int j = 0; j < 9; ++j)
			board[i][j] = rand() % 9;
}

// checks all of the rows of the board
// return 1 if it is correct
// return 0 if it is incorrect
void *row_check(void *arg) {
	printf("running row thread\n");

	// TODO
	int ret = 1;
	return (void *)ret;
}

// checks all of the cols of the board
// return 1 if it is correct
// return 0 if it is incorrect
void *col_check(void *arg) {
	printf("running col thread\n");

	// TODO
	int ret = 1;
	return (void *)ret;
}

// for square_check
// returns a 1d array listing the contents of the 3by3 square
//  0:(0,0)|1:(0,1)|2:(0,2)		// legend
//  -------+-------+-------		// wirtten as 'square_num:(x, y)'
//  3:(1,0)|4:(1,1)|5:(1,2)
//  -------+-------+-------
//  6:(2,0)|7:(2,1)|8:(2,2)
int *get_square(int square_num) {
	// translating square_num to x, y pos
	int x = (int)(square_num/3);
	int y = (int)(square_num%3);

	// the array we'll save the results to and return
	int ret_array[9] = {0};

	// translate from board to ret_array
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			ret_array[i*3+j] = board[x*3+i][y*3+j];

	return ret_array;
}
// checks that the 3by3 square (0 top left, 1 top-centre, etc)
// return 1 if it is correct
// return 0 if it is incorrect
void *square_check(void *arg) {
	printf("running square thread %d\n", (int)arg);

	// TODO
	int ret = 1;
	int square_num = (int)arg;
	int *square = get_square(square_num);
	return (void *)ret;
}

// return 1 if sudoku board is correctly solved
// return 0 if it is not correctly solved
int is_solved(void) {
	// assume the board will is correctly solved, unless otherwise stated
	int ret = 1;

	// init vars
	pthread_t row_pth;
	pthread_t col_pth;
	pthread_t square_pth[9];

	// create check threads (1 for rows, 1 for cols, 9 for 3by3 squares)
	pthread_create(&row_pth, 0, row_check, (void *)9);
	pthread_create(&col_pth, 0, col_check, (void *)10);
	for (int i = 0; i < 9; ++i)
		pthread_create(&square_pth[i], 0, square_check, (void *)i);

	// get status from row when it joins
	void *row_status;
	pthread_join(row_pth, &row_status);
	if ((int)row_status == 0) ret = 0;

	// get status from col when it joins
	void *col__status;
	pthread_join(col_pth, &col__status);
	if ((int)col__status == 0) ret = 0;

	// get status from each square when it joins
	for (int i = 0; i < 9; ++i) {
		void *square_status;
		pthread_join(square_pth[i], &square_status);
		if ((int)square_status == 0) ret = 0;
	}

	return ret;
}


// solves the sudoku board 2d array
void solve (void) {
	// TODO
}
