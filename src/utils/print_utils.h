#ifndef SPA_PRINT_UTILS_H_
#define SPA_PRINT_UTILS_H_

#include <stdio.h>

void print_integers(int *numbers, int count);
void print_integers_wrapped(int *numbers, int count, int max_columns);
void print_matrix(int **matrix, int m, int n);

#endif
