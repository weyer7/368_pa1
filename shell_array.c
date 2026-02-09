#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

static void Array_Debug_Print(const long *, int);

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

    // //print to verify
    // printf("Read from file:\n");
    // for (int i = 0; i < *size; i ++) {
    //     printf("%d - %ld\n", i, arrptr[i]);
    // }
    printf("Read %d elements\n", *size);

    fclose(fptr);

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
    if (!array || size <= 1) return;

    *n_comp = 0;
    int seq_size;

    // Generate 2^p * 3^q gap sequence
    long *gap_seq = Generate_2p3q_Seq(size, &seq_size);

    int count = 0;

    // Outer gap loop (same as list)
    for (int gap = gap_seq[seq_size - 1];
         count < seq_size;
         gap = gap_seq[seq_size - (1 + count)])
    {
        count++;

        int swapped = 1;

        // Repeated bubble passes for this gap
        while (swapped) {
            swapped = 0;

            // One bubble pass
            for (int i = 0; i + gap < size; i++) {
                (*n_comp)++;
                if (array[i] > array[i + gap]) {
                    long tmp = array[i];
                    array[i] = array[i + gap];
                    array[i + gap] = tmp;
                    swapped = 1;
                }
            }
        }
    }
    // Array_Debug_Print(array, size);
    free(gap_seq);
}

static void Array_Debug_Print(const long *array, int size) {
    if (!array) {
        printf("(null array)\n");
        return;
    }

    printf("[");
    for (int i = 0; i < size; i++) {
        printf("[%d] %ld\n", 1, array[i]);
    }
    printf("]\n");
}

    // while (gap > 0) {
    //     while (idx1 < gap) {
    //         while (idx2 < size) {
    //             //compare and swap
    //             (*n_comp) ++;
    //             if (array[idx1] > array[idx2]) {
    //                 temp = array[idx2];
    //                 array[idx2] = array[idx1];
    //                 array[idx1] = temp;
    //             }
    //             idx1 += gap;;
    //             idx2 += gap;
    //         }
    //         subpass ++;
    //         idx1 = subpass;
    //         idx2 = idx1 + gap;
    //     }
    //     gap /= 2;
    //     idx1 = 0;
    //     idx2 = idx1 + gap;
    //     subpass = 0;
    // }