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

#include <mpi.h>
#include <stdio.h>
#include "utils/read_utils.h"
#include "utils/sort_utils.h"
#include "utils/redtree_utils.h"
#include "utils/print_utils.h"
#include "utils/mpi_utils.h"

int main(int argc, char** argv) {
    int res;
    int i;
    int *array;
    int len;
    int pre_len;
    int levels;
    int neighbor;
    int processors;
    int rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &processors);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc < 2) {
        printf("Missing file name argument.");
        return 1;
    }
    
    res = redtree_levels(processors, &levels);
    if (res != 0) {
        printf("unable to get levels: %d\n", res);
        return res;
    }

    if (rank == 0) {
        res = read_integers_from_file(argv[1], &array, &len);
        if (res != 0) {
            printf("Unable to read from file: %d\n", res);
            return res;
        }
        
        printf("This is the master, levels: %d\n", levels);
        printf("This is the master, intial len: %d\n", len);
    
        res = mpi_utils_master_distribute_array(processors, array, len);
        if (res != 0) {
            printf("Unable to distribute array: %d\n", res);
            free(array);
            return res;
        }
        array = realloc(array, sizeof(int) * len / processors);
        len = len / processors;
    } else {
        res = mpi_utils_receive_array(0, &array, &len);
        if (res != 0) {
            printf("unable to receive slice: %d\n", res);
            return res;
        }
    }

    // Everybody sort your arrays
    res = merge_sort(array, len);
    if (res != 0) {
        printf("unable to sort my array: %d", res);
        free(array);
        return res;
    }
 
    //printf("Rank %d: my len %d\n", rank, len);

    for (i = 0; i < levels; i++) {
        neighbor = redtree_get_neighbor(i, rank);
        if (!redtree_is_receiver(i, rank)) {
            //printf("Rank %d: sending len %d\n", rank, len);
            res = mpi_utils_send_array(neighbor, array, len);
            if (res != 0) {
                printf("Unable to send array: %d\n", res);
                free(array);
                return res;
            }
            break;
        }
        pre_len = len;
        res = mpi_utils_combine_arrays(neighbor, &array, &len);
        if (res != 0) {
            printf("Unable to combine arrays: %d\n", res);
            free(array);
            return res;
        }
        res = merge_sorted_partitions(array, pre_len, len - pre_len);
        if (res != 0) {
            printf("Unable to merge partitions: %d\n", res);
            free(array);
            return res;
        }

    }

    if (rank == 0) {
        printf("This is the master, final len: %d\n", len);
        print_integers(array, len);
    }

    free(array);

    MPI_Finalize();
}

