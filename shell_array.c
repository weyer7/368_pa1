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

    return arrptr;
}

int Array_Save_To_File(char *filename, long *array, int size) {
    FILE* fptr = fopen(filename, "wb"); //open bin file (write)
    if (!fptr) {
        printf ("fopen error\n");
        return -1;
    }

    if (!array) {
        return -1;
    }

    //read files into array
    fseek(fptr, 0, SEEK_SET); //reset fptr
    size_t written = fwrite(array, sizeof(long), size, fptr);
    fclose (fptr);
    return written;
}

void Array_Shellsort(long *array, int size, long *n_comp) {

}