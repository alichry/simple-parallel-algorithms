#include <stdio.h>
#include <stdlib.h>

// Set the file name we are reading from:
#define FILE_NAME "input.txt"
// open file in read only mode
#define MODE_READONLY "r"
// open file in read/write mode, the file must exists
#define MODE_READWRITE "r+"
// open the file in read/write mode, the file doesnt have to necessarily exist
#define MODE_READWRITE_SAFE "w+"

void print_numbers(int *numbers, int count, int max_columns)
{
    int i;
    int j = 1;
    // we use max_columns to wrap the printing digits
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

int main()
{
    // declare result variable that we will store the result of a certain
    // function
    int res;
    int i;
    // declare file handle that we will use
    FILE *file;
    // "N" will store the number of integers we're gonna read
    // (N is read from the file, 1st integer to read)
    int N;
    // declare a pointer to integers, that will be treated as an array
    int *numbers;
    // use fopen to stream open a file
    file = fopen(FILE_NAME, MODE_READONLY);
    // we check if the file opened successfuly by checking if the returned pointer
    // is NULL
    if (file == NULL) {
        // check "man perror", or duckduckgo: man perror
        // to view the manual for "perror"
        perror("Unable to open file: ");
        return 1;
    }
    // we assume the first integer represents the count of integers to read from
    // the file
    // in fscanf, we pass a pointer and not the integer value itself as the last parameter
    res = fscanf(file, "%d", &N);
    // fscanf returns the number of element scanned/converted, here we are scanning for only
    // 1 element, therefore we are expecting the result to be "1"
    if (res != 1) {
        printf("fscanf failure, returned: %d", res);
        fclose(file);
        return 1;
    }
    // allocate memory for the integers we're gonna store
    numbers = malloc(sizeof(int) * N);
    // numbers == NULL implies memory allocation failure
    if (numbers == NULL) {
        printf("Cant allocate memory");
        fclose(file);
        return 1;
    }
    for (i = 0; i < N; i++) {
        // numbers + 0 is a pointer that points to the first integer stored in memory
        // numbers + 1 is a pointer that points to the second integer stored in memory
        // and so on, here we itrate from i = 0 to i = N - 1
        res = fscanf(file, "%d", numbers + i);
        if (res != 1) {
            printf("fscanf failure, returned: %d", res);
            // in case fscanf failed, we just close the file we opened and we free the
            // memory allocated for our numbers.
            fclose(file);
            free(numbers);
            return 1;
        }
    }
    printf("Printing numbers...\n");
    print_numbers(numbers, N, 5);
    return 0;
}

