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
    } else {return ptr;}
    long two, three;
    two = 2; three = 3;
    for (int i = 1; i < *seq_size; i ++) {
        if (two < three) {
            ptr[i] = two;
            two += 2;
        } else if (two > three) {
            ptr[i] = three;
            three += 3;
        } else {
            *(ptr + i) = two;
            two += 2;
            three += 3;
        }
        printf("%ld\n", ptr[i]);
    }

    //returns the address of an array of long ints
    return ptr;
}
