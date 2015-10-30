/*
 * Lab 3 SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */

#ifndef UTILITY_H_
#define UTILITY_H_

int field[9][9];

extern void print_field(void);
extern void load_field(char *file_name);

// the threads to check that the field is solved
extern void *row_check(void *arg);
extern void *col_check(void *arg);
extern void *square_check(void *arg);

extern int is_solved();


#endif /* UTILITY_H_ */
