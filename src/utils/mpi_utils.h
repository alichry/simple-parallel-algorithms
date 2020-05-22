#ifndef SPA_MPI_UTILS_H_
#define SPA_MPI_UTILS_H_

#include <mpi.h>
#include <stdlib.h>
#include "err.h"

/**
 * mpi_utils_send_array:
 * @arg to - the rank/processor id to send the array to
 * @arg array - a pointer... the array
 * @arg len - the lengtho of the array
 * @return - 0 on success and non-zero on error.
 * This function will send the array to processor -to-
 * Sending the array is done by first sending the "len" to "to" then sending
 * the array data.
 */
int mpi_utils_send_array(int to, int *array, int len);

/**
 * mpi_utils_receive_array:
 * @arg from: the rank/processor id we are expecting to receive the array from
 * @arg array - output - a pointer to an array. Must be a non-initialized poiner
 * @arg len - output - a pointer to an integer that will represent the len
 * @return - 0 on success, non-zero otherwise.
 * This function will receive an array by first receiving the array length
 * from "from", allocates memory for the array and storing the pointer value in
 * array and finally reciving the array data from "from"
 * Note: we are passing a pointer to a pointer of type int... This simply
 * implies that we want to change the value pointed by the pointer to an int to
 * a memory address we will allocate in the function.
 * After a call to this function, the 2nd parameter should be a valid pointer
 * and the third parameter should represent the array length received from
 * "from".
 * The caller of this function is responsible of free'ing the array.
 */
int mpi_utils_receive_array(int from, int **array, int *len);

/**
 * mpi_utils_master_distribute_array:
 * @arg processors - the number of processors
 * @arg array - the buffer...//array... a pointer
 * @arg len - the length of the array
 * @return - 0 on sucess, non-zero otherwise
 * This method acts like an MPI Scatter but will send the last processor the
 * trailing data elements in case the length is not divisible by the number of
 * processors.
 */
int mpi_utils_master_distribute_array(int processors, int *array, int len);

/**
 * mpi_utils_combine_arrays:
 * @arg from - the processor we are receiving and combine its array from.
 * @arg array - output - the address of the array pointer..
 * @arg len - output - a pointer to int, this variable will contain the 
 * array length after the call.
 * @return - 0 on success, non-zero otherwise.
 * This method will acct like mpi_utils_receive_array but instead of just
 * providing a valid-pointer, it will combine the data elements to the 
 * existing array passed as the 2nd parameter. It will append the sender's
 * element to the end of the array.
 */
int mpi_utils_combine_arrays(int from, int **array, int *len);

/**
 * mpi_utils_send_int:
 * @arg value - a simple integer, not a pointer, just the value
 * @arg to - the processor/rank id to send to.
 * @return - 0 on success, non-zero otherwise.
 * This will simply send an integer.
 */
int mpi_utils_send_int(int value, int to);

/**
 * mpi_utils_receive_int:
 * @arg ret - output - a pointer to int
 * @arg from - the processor/rank id to receive the int from
 * @return - 0 on sucess, non-zero otherwise
 * The first parameter is a pointer, .... i.e. referencing an integer will get oyu a pointer... e.g. &value
 */ 
int mpi_utils_receive_int(int *ret, int from);

#endif
