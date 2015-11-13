/*
 * Lab 3 SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */

#include "utility.h"
#include <pthread.h>
#include <stdio.h>

#define RED "\x1b[0;31m" // 41m for background
#define RESET "\x1b[0m"

// our 9 by 9 sudoku board
int board[9][9];
pthread_mutex_t board_lock;

// print the current board 2d array (9 by 9) to the console
void print_board(void) {
	// go through every element of board array
	for(int i = 0; i < 9; ++i) {
		// print horizontal line before each third
		if (i%3 == 0)
			printf(RESET "+-------+-------+-------+\n");

		for(int j = 0; j < 9; ++j) {
			// print bar at the start of a new line
			if (j == 0)
				printf(RESET "| ");

			// use escape sequences to output '0' in red
			if(board[i][j] == 0)
				printf(RED);
			else
				printf(RESET);

			// output the element
			printf("%d ", board[i][j]);

			// print bar after every third
			if (j%3 == 2)
				printf(RESET "| ");
		}
		printf("\n");
	}

	// escape sequence to reset terminal color
	printf(RESET);

	// final horizontal line
	printf("+-------+-------+-------+\n");
}

// loads in the input file from filename, and saves it to the board 2d array
void load_board(char *file_name) {
	const int MAX_LINE = 19; // 9 numbers, 9 spaces, and \n
	static char line[MAX_LINE] = "";
	char *token_str;

	// open the file
	FILE *f = fopen(file_name, "r");
	if(f == NULL) {
		fprintf(stderr, "unable to open file for reading");
		return;
	}

	// read in each line
	for (int i = 0; fgets(line, MAX_LINE, f) != NULL && i < 9; i++) {
		// the tokenizer must init with line, and after that it will take NULL
		if ((token_str = strtok(line, " ")) != NULL)
			board[i][0] = atoi(token_str);

		// go through each of the remaining elements in the row
		for (int j = 1; j < 9; j++)
			if ((token_str = strtok(NULL, " ")) != NULL)
				board[i][j] = atoi(token_str);
	}

	// close the file
	fclose(f);
}

// saves the board array to output filename
void save_board(char * file_name) {
	const int MAX_LINE = 19; // 9 numbers, 9 spaces, and \n
	static char line[MAX_LINE] = "";

	// open the file
	FILE *f = fopen(file_name, "w");
	if(f == NULL) {
		fprintf(stderr, "unable to open file for reading");
		return;
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fprintf(f, "%d ", board[i][j]);
		}
		fprintf(f, "\n");
	}

	// close the file
	fclose(f);
}

// checks if there are any duplicates in the input array of 9 elements
// return 0 if there are no duplicates
// return 1 if there is at least one duplicate
int contains_duplicate(int a[9]) {
	for (int i = 0; i < 8; i++)
		for (int j = i+1; j < 9; j++)
			if (a[i] == a[j])
				return 1;

	return 0;
}

// checks if the array contains a zero
// return 0 if it doesn't contain a zero
// return 1 if it contains a zero
int contains_zero(int a[9]) {
	for (int i = 0; i < 9; i++)
		if (a[i] == 0)
			return 1;

	return 0;
}

// for square_check
// puts a 1d array listing the contents of the 3by3 square in ret_array
//  0:(0,0)|1:(0,1)|2:(0,2)		// legend
//  -------+-------+-------		// wirtten as 'square_num:(x, y)'
//  3:(1,0)|4:(1,1)|5:(1,2)
//  -------+-------+-------
//  6:(2,0)|7:(2,1)|8:(2,2)
void get_square(int *ret_array, int square_num) {
	// translating square_num to x, y pos
	int x = (int)(square_num/3);
	int y = (int)(square_num%3);

	// translate from board to ret_array
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			ret_array[i*3+j] = board[x*3+i][y*3+j];
}

// puts a 1d array listing the contents of row i
void get_row(int *ret_array, int i) {
	for (int j = 0; j < 9; j++)
		ret_array[j] = board[i][j];
}

// puts a 1d array listing the contents of column j
void get_col(int *ret_array, int j) {
	for (int i = 0; i < 9; i++)
		ret_array[i] = board[i][j];
}

// checks all of the rows of the board
// return 1 if it is correct
// return 0 if it is incorrect
void *row_check(void *arg) {
	// go through each row
	for (int i = 0; i < 9; i++) {
		int row[9] = {0};

		// lock the board before accessing it
		pthread_mutex_lock(&board_lock);
		// copy the column into a spearate array
		get_row(&row, i);
		pthread_mutex_unlock(&board_lock);

		// that actual check
		if (contains_zero(row) || contains_duplicate(row))
			return (void *)0;
	}

	return (void *)1;
}

// checks all of the cols of the board
// return 1 if it is correct
// return 0 if it is incorrect
void *col_check(void *arg) {
	// go through each column
	for (int j = 0; j < 9; j++) {
		int col[9];

		// lock the board before accessing it
		pthread_mutex_lock(&board_lock);
		// copy the column into a spearate array
		get_col(&col, j);
		pthread_mutex_unlock(&board_lock);

		// the actual check
		if (contains_zero(col) || contains_duplicate(col))
			return (void *)0;
	}

	return (void *)1;
}

// checks that the 3by3 square (0 top left, 1 top-centre, etc)
// return 1 if it is correct
// return 0 if it is incorrect
void *square_check(void *arg) {
	int square_num = (int)arg;

	// lock the board before accessing it
	pthread_mutex_lock(&board_lock);
	int square[9];
	get_square(&square, square_num);
	pthread_mutex_unlock(&board_lock);

	// the actual check
	if (contains_zero(square) || contains_duplicate(square))
		return (void *)0;

	return (void *)1;
}

// determines if the board 2d array is a solved sudoku puzzle
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
	pthread_create(&row_pth, 0, row_check, (void *)NULL);
	pthread_create(&col_pth, 0, col_check, (void *)NULL);
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

// counts the number of non-zero elements in array a
// returns the total count
int element_count(int a[9], int start, int end) {
	int count = 0;
	for (int i = start; i < end; i++)
		if (a[i] != 0)
			count++;

	return count;
}

// sets a cell if it can safely be set
// returns 1 if the cell was set
// returns 0 if no cell was set
int check_and_set_cell(int i, int j) {
	int col[9] = {0};
	int row[9] = {0};
	int square[9] = {0};
	int is_taken[10] = {0}; // bool array of unavailable numbers to our current cell

	// create a list of numbers that intersect our cell (same row, col, or square)
	get_row(&row, i);
	get_col(&col, j);
	int square_num = (i/3)*3 + (j/3);
	get_square(&square, square_num);

	for (int x = 0; x < 9; x++) {
		is_taken[col[x]] = 1;
		is_taken[row[x]] = 1;
		is_taken[square[x]] = 1;
	}

	// the cell can be solved
	if (element_count(is_taken, 1, 10) == 8) {
		// get the number
		for (int x = 1; x < 10; x++) {
			if (is_taken[x] == 0) {
				board[i][j] = x;
				return 1;
			}
		}
	}

	return 0;
}

// solves the sudoku board 2d array
// solves 'safe' puzzles, that is puzzles that never require guessing
void solve (void) {
	int change_count;
	do {
		// keep track if any changes are made
		change_count = 0;

		// go through each cell of the board
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				// only try to solved unsolved cells
				if (board[i][j] == 0) {
					change_count += check_and_set_cell(i, j);
				}
			}
		}
	} while (change_count > 0);
}
