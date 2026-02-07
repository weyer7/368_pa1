#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"

long *Array_Load_From_File(char *filename, int *size) {
    // long num_elements = *size / sizeof(long);
    FILE* fptr = fopen(filename, "rb"); //open bin file (read)
    if (!fptr) {
        printf ("fopen error\n");
        return NULL; //return NULL
    }

    if (fseek(fptr, 0, SEEK_END) != 0) {
        printf ("can't find EOF\n");
        fclose(fptr);
    }

    *size = ftell(fptr) / sizeof(long); //gets current read position

    long *arrptr;
    arrptr = (long *)malloc(*size * sizeof(long)); //will have to free in a clean program
    if (!arrptr) {
        printf ("malloc error\n");
        return NULL;
    }
    //read files into array
    fseek(fptr, 0, SEEK_SET); //reset fptr
    fread(arrptr, sizeof(long), *size, fptr);

    //print to verify
    printf("Read from file:\n");
    for (int i = 0; i < *size; i ++) {
        printf("%d - %ld\n", i, arrptr[i]);
    }
    printf("Read %d elements\n", *size);
}