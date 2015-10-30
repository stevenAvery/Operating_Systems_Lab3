/*
 * Lab 3 SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */


#include "utility.h"
#include <pthread.h>

// print the current field
void print_field(int field[9][9]) {
	// TODO
}

// loads in the input file, pasres it and saves it as a 2d array
int** load_field(char *file_name) {
	// TODO
	int field[9][9] = {{0, 0}};
	return field;
}


// checks the rows of the field
void *row_check(void *arg) {
	// TODO
	pthread_exit(NULL);
}


// checks the cols of the field
void *col_check(void *arg) {
	// TODO
	pthread_exit(NULL);
}
