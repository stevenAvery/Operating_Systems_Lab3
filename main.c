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

extern int is_solved();

typedef struct
{
    int row;
    int column;
} parameters;

int main(void) {
	load_field(INPUT_FILE);

	if (is_solved()) {
		printf("file succesfully solved\n");
		print_field();
	} else {
		printf("error solving file\n");
	}


	return 0;
}
