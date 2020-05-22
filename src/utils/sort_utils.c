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

#include "sort_utils.h"

int merge_sorted_partitions(int *arr, int part1_len, int part2_len)
{
    int i, j, t;
    int *tmp;
    int total_len;
    i = 0;
    j = part1_len;
    t = 0;
    total_len = part1_len + part2_len;
    tmp = malloc(sizeof(int) * total_len);
    if (tmp == NULL) {
        return SPA_UTILS_ECANTALLOC;
    }
    while (i < part1_len && j < part1_len + part2_len) {
        if (arr[i] <= arr[j]) {
            tmp[t++] = arr[i++];
        } else {
            tmp[t++] = arr[j++];
        }
    }
    if (i >= part1_len) {
        memcpy(tmp + t, arr + j, sizeof(int) * (part1_len + part2_len - j));
    } else {
        memcpy(tmp + t, arr + i, sizeof(int) * (part1_len - i));
    }
    memcpy(arr, tmp, sizeof(int) * total_len);
    free(tmp);
    return 0;
}

int merge_sort(int *arr, int length)
{
    int *tmp;
    tmp = malloc(sizeof(int) * length);
    if (tmp == NULL) {
        return SPA_UTILS_ECANTALLOC;
    }
    merge_sort_divide(arr, tmp, 0, length - 1);
    free(tmp);
    return 0;
}

void merge_sort_divide(int *arr, int *tmp, int start, int end)
{
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort_divide(arr, tmp, start, mid);
    merge_sort_divide(arr, tmp, mid + 1, end);
    merge_sort_dm(arr, tmp, start, end);
}

void merge_sort_dm(int *arr, int *tmp, int start, int end)
{
    int i, j, c;
    int mid;

    c = 0;
    i = start;
    mid = (start + end) / 2;
    j = mid + 1;
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            tmp[c++] = arr[i++];
        } else {
            tmp[c++] = arr[j++];
        }
    }
    // check where we stopped....
    if (i > mid) {
        // we copied all elements in before mid, copy 
        // the remaining elements in from j till end
        memcpy(tmp + c, arr + j, sizeof(int) * (end - j + 1));
    } else {
        // otherwise....
        memcpy(tmp + c, arr + i, sizeof(int) * (mid - i + 1));
    }
    // copy the resuls..
    memcpy(arr + start, tmp, sizeof(int) * (end - start + 1));
}
