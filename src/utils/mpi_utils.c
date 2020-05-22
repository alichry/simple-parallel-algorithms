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

#include "mpi_utils.h"

int mpi_utils_send_array(int to, int *array, int len)
{
    MPI_Send(&len, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
    MPI_Send(array, len, MPI_INT, to, 0, MPI_COMM_WORLD);
    return 0;
}

int mpi_utils_receive_array(int from, int **array, int *len)
{
    int *narray;
    int slice = -1;
    MPI_Recv(&slice, 1, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    narray = malloc(sizeof(int) * slice);
    if (narray == NULL) {
        return SPA_UTILS_ECANTALLOC;
    }
    *array = narray;
    MPI_Recv(*array, slice, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    *len = slice;
    return 0;
}

int mpi_utils_master_distribute_array(int processors, int *array, int len)
{
    int i;
    int slice;
    int res;
    int slave_slice;
    slice = len / processors;

    for (i = 1; i < processors; i++) {
        if (i == processors - 1) {
            slave_slice = slice + len %  processors;
        } else {
            slave_slice = slice;
        }
        res = mpi_utils_send_array(i, array + slice * i, slave_slice);
        if (res != 0) {
            return res;
        }
    }
    return 0;
}

int mpi_utils_combine_arrays(int from, int **array, int *len)
{
    int other_len;
    int new_len;
    int *narray;
    MPI_Recv(&other_len, 1, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    new_len = *len + other_len;
    narray = realloc(*array, sizeof(int) * new_len);
    if (narray == NULL) {
        return SPA_UTILS_ECANTALLOC;
    }
    *array = narray;
    MPI_Recv(narray + *len, 
            other_len, 
            MPI_INT, from, 
            0, 
            MPI_COMM_WORLD, 
            MPI_STATUS_IGNORE);
    *len = new_len;
    return 0;
}

int mpi_utils_send_int(int value, int to)
{
    MPI_Send(&value, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
    return 0;
}

int mpi_utils_receive_int(int *ret, int from)
{
    MPI_Recv(ret, 1, MPI_INT, from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return 0;
}
