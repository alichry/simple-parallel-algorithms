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

#include "matrix_utils.h"

int matrix_multiplication
(int **A, int ma, int na, int **B, int mb, int nb, int ***r_C, int *r_mc, 
 int *r_nc)
{
    int res;
    int i, j;
    int mc, nc;
    int **C;
    mc = ma;
    nc = nb;
    if (na != mb) {
        // matrices are not compatible
        return SPA_UTILS_EMATRICESINCOMP;
    }
    res = matrix_allocate(mc, nc, &C);
    if (res != 0) {
        return res;
    }
    for (i = 0; i < mc; i++) {
        for (j = 0; j < nc; j++) {
            C[i][j] = matrix_multiplication_compute_value
                (A, B, na /* or mb */, i, j);
        }
    }
    *r_C = C;
    *r_mc = mc;
    *r_nc = nc;
    return 0;
}

int matrix_multiplication_compute_value(int **A, int **B, int n, int i, int j)
{
    int u;
    int result = 0;
    for (u = 0; u < n; u++) {
        result += A[i][u] * B[u][j];
    }
    return result;
}

int matrix_allocate(int m, int n, int ***r_matrix)
{
    int i;
    int **matrix;
    if (m <= 0 || n <= 0) {
        return SPA_UTILS_EBADINPUT;
    }
    matrix = malloc(sizeof(int *) * m);
    if (matrix == NULL) {
        return SPA_UTILS_ECANTALLOC;
    }
    for (i = 0; i < m; i++) {
        *(matrix + i) = malloc(sizeof(int) * n);
        if (*(matrix + i) == NULL) {
            if (i != 0) {
                matrix_free_range(matrix, 0, i - 1);
            }
            return SPA_UTILS_ECANTALLOC;
        }
    }
    *r_matrix = matrix;
    return 0;
}

int matrix_free(int **matrix, int m)
{
    int res;
    if (m <= 0) {
        return SPA_UTILS_EBADINPUT;
    }
    res = matrix_free_range(matrix, 0, m - 1);
    if (res != 0) {
        return SPA_UTILS_EBADINPUT;
    }
    free(matrix);
    return 0;
}

int matrix_free_range(int **matrix, int start_row, int end_row)
{
    int i;
    if (start_row > end_row) {
        return SPA_UTILS_EBADINPUT;
    }
    if (start_row < 0 || end_row < 0) {
        return SPA_UTILS_EBADINPUT;
    }
    for (i = start_row; i <= end_row; i++) {
        free(*(matrix + i)); 
    }
    return 0;
}

