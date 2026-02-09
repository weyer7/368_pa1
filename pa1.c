#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"

static void Free_List (Node *);

//all helper functions must be static
//no math.h
//do not modify header files

// int main(int argc, char const *argv[])
// {
//     /* code */
//     int size;
//     long n_comp;
//     // printf("test\n\n");
//     // long *my_gaps = Generate_2p3q_Seq(1000 /*num ints*/, &size /*num elements*/);
//     // long *arr = Array_Load_From_File("examples/1M.b", &size);
//     // Array_Shellsort(arr, size, &n_comp);
//     // Array_Save_To_File("outputs/1M.b", arr, size);
//     // Array_Load_From_File("outputs/1M.b", &size);
//     int status;
//     Node *list = List_Load_From_File("examples/15.b", &status);
//     List_Shellsort(list, &n_comp);
//     List_Save_To_File("outputs/15_ll.b", list);
//     return 0;
// }

int main(int argc, char const *argv[])
{
    int size;
    long n_comp = 0;

    const char *mode   = argv[1];
    const char *input  = argv[2];
    const char *output = argv[3];

    /* ARRAY SHELLSORT */
    if (strcmp(mode, "-a") == 0) {

        long *arr = Array_Load_From_File(input, &size);
        if (!arr) {
            printf("Failed to load array from %s\n", input);
            return -1;
        }

        Array_Shellsort(arr, size, &n_comp);

        if (Array_Save_To_File(output, arr, size) == -1) {
            printf("Failed to save array to %s\n", output);
            free(arr);
            return -1;
        }

        free(arr);
    }

    /* LINKED LIST SHELLSORT */
    else if (strcmp(mode, "-l") == 0) {

        int status;
        Node *list = List_Load_From_File(input, &status);
        if (status == -1) {
            printf("Failed to load list from %s\n", input);
            return -1;
        }

        list = List_Shellsort(list, &n_comp);

        if (List_Save_To_File(output, list) == -1) {
            printf("Failed to save list to %s\n", output);
            return -1;
        }
        Free_List(list);
    }

    else {
        printf("Unknown option: %s\n", mode);
        return -1;
    }

    return 0;
}

static void Free_List (Node *list) {
    Node *next = list;
    while (list) {
        next = list->next;
        free(list);
        list = next;
    }
}
