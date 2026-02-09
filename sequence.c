#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

long *Generate_2p3q_Seq(int n, int *seq_size) {  
    if (seq_size == NULL) {
        return NULL;
    }
    if (n <= 1) {
        *seq_size = 0;
        return NULL;
    }
    //determine the length of the sequence
    int count = 0;
    for (long long p2 = 1; p2 < n; p2 *= 2) {
        for (long long p23 = p2; p23 < n; p23 *= 3) {
            count++;
        }
    }
    *seq_size = count;

    //alocate array memory
    long *ptr = (long *)malloc(count * sizeof(long)); //has to be freed later
    if (!ptr) {
        printf("malloc failed!\n");
        return NULL;
    }

    //re-calculate sequence
    ptr[0] = 1;
    int p = 0; 
    int q = 0; 
    int idx = 1;

    while (idx < count) {
        long next_2 = ptr[p] * 2;
        long next_3 = ptr[q] * 3;

        if (next_2 < next_3) {
            ptr[idx] = next_2;
            p++;
        } else if (next_3 < next_2) {
            ptr[idx] = next_3;
            q++;
        } else {
            ptr[idx] = next_2;
            p++;
            q++;
        }
        idx++;
    }

    //debug print
    for (int i = 0; i < *seq_size; i++) {
        printf(" [%d] %ld\n", i, ptr[i]);
    }
    printf("\n");

    return ptr;
}