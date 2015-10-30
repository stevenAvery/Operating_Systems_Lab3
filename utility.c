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
void print_field(void) {
	// TODO
}

// loads in the input file, pasres it and saves it as a 2d array
void load_field(char *file_name) {
	// TODO
	int field[9][9] = {{0, 0}};
}


// checks the rows of the field
void *row_check(void *arg) {
	// TODO
	int ret = 0;
	pthread_exit(&ret);
}


// checks the cols of the field
void *col_check(void *arg) {
	// TODO
	int ret = 0;
	pthread_exit(&ret);
}

// checks that the 3by3 square (0 top left, 1 top-centre, etc)
void *square_check(void *arg) {
	// TODO
	int ret = 0;
	pthread_exit(&ret);
}


int is_solved() {
	pthread_t row_check_thread;
	pthread_t col_check_thread;
	pthread_t square_check_thread[9];

	// create all of the check threads
	pthread_create(&row_check_thread, NULL, row_check, (void *)NULL);
	pthread_create(&col_check_thread, NULL, col_check, (void *)NULL);
	for(int i = 0; i < 9; ++i)
		pthread_create(&square_check_thread, NULL, square_check, (void *)i);

	// assume its solved
	void *return_val = 1;

	// join back in all of the check threads
	pthread_join(row_check_thread, &return_val);
	printf("%d\n", *(int *)return_val);
	//if (*(int *)return_val) return 0;

	pthread_join(col_check_thread, &return_val);
	printf("%d\n", *(int *)return_val);

	for(int i = 0; i < 9; ++i) {
		pthread_join(square_check_thread, &return_val);
		printf("%d\n", *(int *)return_val);
	}

	return 1;
}
