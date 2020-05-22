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
