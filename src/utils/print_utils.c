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

#include "print_utils.h"

void print_integers(int *numbers, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

void print_integers_wrapped(int *numbers, int count, int max_columns)
{
    int i;
    int j = 1;
    // we use max_columns to wrap the the printed characters
    for (i = 0; i < count; i++) {
        printf("%d  ", numbers[i]);
        j++;
        if (j == max_columns) {
            j = 0;
            printf("\n");
        }
    }
    if (j != 0) {
        printf("\n");
    }
}

void print_matrix(int **matrix, int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
