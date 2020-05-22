#ifndef SPA_MATRIX_UTILS_H_
#define SPA_MATRIX_UTILS_H_

#include <stdlib.h>
#include "err.h"

int matrix_multiplication
(int **a, int ma, int na, int **b, int mb, int nb, int ***r_c, int *r_mc, 
 int *r_nc);
int matrix_multiplication_compute_value(int **A, int **B, int n, int i, int j);

int matrix_allocate(int m, int n, int ***r_matrix);
int matrix_free_range(int **matrix, int start_row, int end_row);
int matrix_free(int **matrix, int m);

#endif
