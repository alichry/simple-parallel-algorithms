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
