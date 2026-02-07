#include <stdio.h>
#include <stdlib.h>
long *Generate_2p3q_Seq(int, int*);

long *Generate_2p3q_Seq(int n /*num ints*/, int *seq_size /*num elements*/)
{
    //ceil(n/2)
    *seq_size = (n + 1) / 2;

    long *ptr;
    ptr = (long *)malloc(*seq_size * sizeof(int)); //will have to free in a clean program
    if (!ptr) {
        printf("malloc failed");
    }

    if (n > 0) {
        ptr[0] = 1;
        printf("%ld\n", ptr[0]);
    } else {return ptr;}
    long p, q, two_n, three_n;
    p = 0; q = 0;
    for (int i = 1; i < *seq_size; i ++) {
        two_n = ptr[p] * 2;
        three_n = ptr[q] * 3;

        //choose smallest
        if (two_n < three_n) {
            ptr[i] = two_n;
            p ++;
        } else if (two_n > three_n) {
            ptr[i] = three_n;
            q ++;
        } else {
            ptr[i] = two_n;
            p ++; q ++;
        }
        printf("p:%ld, q:%ld, %ld\n", p, q, ptr[i]);
    }

    //returns the address of an array of long ints
    return ptr;
}
