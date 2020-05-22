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

#include "utils/read_utils.h"
#include "utils/print_utils.h"
#include "utils/matrix_utils.h"

int main(int argc, char **argv)
{
    int res;
    char *input;
    int **A, **B, **C;
    int ma, na, mb, nb, mc, nc;
    if (argc != 2) {
        printf("Sequential matrix multiplication usage:\n"
               "\t%s <input>\n", argv[0]);
        return 1;
    }
    input = argv[1];
    res = read_matrices_from_file(input, 
            &A, &B, &ma, &na, &mb, &nb);
    if (res != 0) {
        fprintf(stderr, "cant read matrices, error: %d\n", res);
        return 1;
    }
    printf("Printing matrix A\n");
    print_matrix(A, ma, na);
    printf("Printing matrix B\n");
    print_matrix(B, mb, nb);
    printf("Computing A.B\n");
    res = matrix_multiplication(A, ma, na, B, mb, nb, &C, &mc, &nc);
    if (res != 0) {
        fprintf(stderr, "matrix_multiplication failure, error: %d\n", res);
        return 1;
    }
    printf("Printing matrix C\n");
    print_matrix(C, mc, nc);
    free_matrix(A, ma);
    free_matrix(B, mb);
    free_matrix(C, mc);
}

