#ifndef SPA_SORT_UTILS_H_
#define SPA_SORT_UTILS_H_

#include "err.h"
#include <stdlib.h>
#include <string.h>

int merge_sort(int *arr, int length);
int merge_sorted_partitions(int *arr, int part1_len, int part2_len);
void merge_sort_divide(int *arr, int *tmp, int start, int end);
void merge_sort_dm(int *arr, int *tmp, int start, int end);

#endif
