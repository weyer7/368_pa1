#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"

//all helper functions must be static
//no math.h
//do not modify header files

int main(int argc, char const *argv[])
{
    /* code */
    int size;
    long n_comp;
    // Generate_2p3q_Seq(21 /*num ints*/, ptr /*num elements*/);
    // long *arr = Array_Load_From_File("examples/1M.b", &size);
    // Array_Shellsort(arr, size, &n_comp);
    // Array_Save_To_File("outputs/1M.b", arr, size);
    // Array_Load_From_File("outputs/1M.b", &size);
    int status;
    Node *list = List_Load_From_File("examples/15.b", &status);
    List_Save_To_File("outputs/15_ll.b", list);
    return 0;
}
