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

extern void *row_check(void *arg);
extern void *col_check(void *arg);


typedef struct
{
    int row;
    int column;
} parameters;

int main(void) {
	int field = load_field(INPUT_FILE);

	pthread_t row_check_thread;
	pthread_t col_check_thread;

	pthread_create(&row_check_thread, 0, row_check, (void *)NULL);
	pthread_create(&col_check_thread, 0, col_check, (void *)NULL);

	pthread_join(row_check_thread, 0);
	pthread_join(col_check_thread, 0);


	print_field(field);

	return 0;
}
