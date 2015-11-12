/*
 * Lab 3 SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */

#include "stdio.h"
#include "utility.h"
#include <pthread.h>

#define INPUT_FILE "puzzle.txt"

int main(void) {
	// load the input file into the our 2d array
	load_board(INPUT_FILE);
	printf("input:\n");
	print_board();

	// if the board is not sovled
	if (!is_solved())
		solve(); // solve it

	// if the board is solved
	else
		printf("the board was already sovled\n");

	// output the solved board
	// printf("\n------------------------------------\n"); // DEBUG
	printf("\nsolution:\n");
	print_board();

	return 0;
}
