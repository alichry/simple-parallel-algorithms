#ifndef SPA_READ_UTILS_H_
#define SPA_READ_UTILS_H_

// open file in read only mode
#define RU_MODE_READONLY "r"
// open file in read/write mode, the file must exists
#define RU_MODE_READWRITE "r+"
// open the file in read/write mode, the file doesnt have to necessarily exist
#define RU_MODE_READWRITE_SAFE "w+"

#include "err.h"
#include <stdlib.h>
#include <stdio.h>

int read_integers_from_file(char *filename, int **r_numbers, int *r_size);
int read_matrices_from_file
(char *filename, int ***r_a, int ***r_b, 
 int *r_ma, int *r_na, int *r_mb, int *r_nb);
void free_matrix(int **matrix, int m);
void free_matrix_range(int **matrix, int start_row, int end_row);
#endif
