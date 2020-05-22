#include "read_utils.h"

int read_integers_from_file(char *filename, int **r_numbers, int *r_size)
{
    int i;
    int res;
    int count;
    FILE *file;
    int *numbers;
    if (r_numbers == NULL) {
        return SPA_UTILS_EBADINPUT;
    }
    if (r_size == NULL) {
        return SPA_UTILS_EBADINPUT;
    }
    file = fopen(filename, RU_MODE_READONLY);
    if (file == NULL) {
        return SPA_UTILS_EFOPEN;
    }
    res = fscanf(file, "%d", &count);
    if (res != 1) {
        fclose(file);
        return SPA_UTILS_EFSCANF;
    }
    numbers = malloc(sizeof(int) * count);
    if (numbers == NULL) {
        fclose(file);
        return SPA_UTILS_ECANTALLOC;
    }
    for (i = 0; i < count; i++) {
        res = fscanf(file, "%d", numbers + i);
        if (res != 1) {
            printf("fscanf failure, returned: %d", res);
            fclose(file);
            free(numbers);
            return SPA_UTILS_EFSCANF;
        }
    }
    *r_numbers = numbers;
    *r_size = count;
    fclose(file);
    return 0;
}

int read_matrices_from_file
(char *filename, int ***r_a, int ***r_b, 
 int *r_ma, int *r_na, int *r_mb, int *r_nb)
{
    int i, j;
    int res;
    int ma, na, mb, nb;
    int tmp;
    int **a;
    int **b;
    FILE *file;
    if (r_a == NULL || r_b == NULL) {
        return SPA_UTILS_EBADINPUT;
    }
    if (r_ma == NULL || r_na == NULL || r_mb == NULL || r_nb == NULL) {
        return SPA_UTILS_EBADINPUT;
    }
    file = fopen(filename, RU_MODE_READONLY);
    if (file == NULL) {
        return SPA_UTILS_EFOPEN;
    }
    // prepare matrix A
    res = fscanf(file, "%d", &ma);
    if (res != 1) {
        fclose(file);
        return SPA_UTILS_EFSCANF;
    }
    res = fscanf(file, "%d", &na);
    if (res != 1) {
        fclose(file);
        return SPA_UTILS_EFSCANF;
    }
    a = malloc(sizeof(int *) * ma);
    if (a == NULL) {
        return SPA_UTILS_ECANTALLOC;
    }
    for (i = 0; i < ma; i++) {
        *(a + i) = malloc(sizeof(int) * na);
        if (*(a + i) == NULL) {
            if (i != 0) {
                free_matrix_range(a, 0, i - 1);
            }
            fclose(file);
            return SPA_UTILS_ECANTALLOC;
        }
    }
    // fill matrix A
    for (i = 0; i < ma; i++) {
        for (j = 0; j < na; j++) {
            res = fscanf(file, "%d", &tmp);
            if (res != 1) {
                free_matrix(a, ma);
                fclose(file);
                return SPA_UTILS_EFSCANF;
            }
            *(*(a + i) + j) = tmp;
        }
    }
    // prepare matrix B
    res = fscanf(file, "%d", &mb);
    if (res != 1) {
        fclose(file);
        return SPA_UTILS_EFSCANF;
    }
    res = fscanf(file, "%d", &nb);
    if (res != 1) {
        fclose(file);
        return SPA_UTILS_EFSCANF;
    }
    b = malloc(sizeof(int *) * mb);
    if (b == NULL) {
        return SPA_UTILS_ECANTALLOC;
        fclose(file);
    }
    for (i = 0; i < mb; i++) {
        *(b + i) = malloc(sizeof(int) * nb);
        if (*(b + i) == NULL) {
            if (i != 0) {
                free_matrix_range(b, 0, i - 1);
            }
            free_matrix(a, ma);
            fclose(file);
            return SPA_UTILS_ECANTALLOC;
        }
    }
    // fill matrix B
    for (i = 0; i < mb; i++) {
        for (j = 0; j < nb; j++) {
            res = fscanf(file, "%d", &tmp);
            if (res != 1) {
                free_matrix(a, ma);
                free_matrix(b, mb);
                fclose(file);
                return SPA_UTILS_EFSCANF;
            }
            *(*(b + i) + j) = tmp;
        }
    }
    fclose(file);
    *r_a = a;
    *r_b = b;
    *r_ma = ma;
    *r_na = na;
    *r_mb = mb;
    *r_nb = nb;
    return 0;
}

void free_matrix(int **matrix, int m)
{
    free_matrix_range(matrix, 0, m - 1);
    free(matrix);
}

void free_matrix_range(int **matrix, int start_row, int end_row)
{
    int i;
    for (i = start_row; i <= end_row; i++) {
        free(*(matrix + i)); 
    }
}

