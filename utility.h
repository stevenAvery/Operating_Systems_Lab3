/*
 * Lab 3 SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 100493227, 100451291, 100462413, 100522340
 * All rights reserved.
 *
 */

#ifndef UTILITY_H_
#define UTILITY_H_

// board data management
extern void print_board(void);
extern void load_board(char *file_name);

// to check that the board is solved
extern int is_duplicate(int a[9]);
extern void *row_check(void *arg);
extern void *col_check(void *arg);
extern void *square_check(void *arg);
extern int is_solved(void);

// solves the board
extern void solve(void);

#endif /* UTILITY_H_ */
