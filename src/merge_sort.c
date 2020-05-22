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

#include "utils/sort_utils.h"
#include "utils/read_utils.h"
#include "utils/print_utils.h"

int main(int argc, char **argv)
{
    char *input;
    int res;
    int *arr;
    int size;
    if (argc != 2) {
        printf("Sequential merge sort usage:\n"
               "\t%s <input>\n", argv[0]);
        return 1;
    }
    input = argv[1];
    res = read_integers_from_file(input, 
            &arr, &size);
    if (res != 0) {
        fprintf(stderr, "cant read ints.\n");
        return 1;
    }
    printf("Printing unsorted array of size %d:\n", size);
    print_integers(arr, size);
    res = merge_sort(arr, size);
    if (res != 0) {
        fprintf(stderr, "cant sort array: %d\n", res);
        return 1;
    }
    printf("Printing sorted array:\n");
    print_integers(arr, size);
    printf("Freeing...\n");
    free(arr);
    return 0;
}
