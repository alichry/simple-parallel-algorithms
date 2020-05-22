/**
 * Copyright 2020 Ali Cherry <cmcrc@alicherry.net>
 * This file is part of Simple Parallel Algorithms (SPA).
 * 
 * SPA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * SPA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SPA.  If not, see <https://www.gnu.org/licenses/>.
 */

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
