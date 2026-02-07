#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"

//all helper functions must be static
//no math.h
//do not modify header files

int main(int argc, char const *argv[])
{
    /* code */
    int *ptr;
    // Generate_2p3q_Seq(21 /*num ints*/, ptr /*num elements*/);
    Array_Load_From_File("examples/1K.b", ptr);
    return 0;
}
