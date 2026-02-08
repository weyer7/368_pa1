#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"

static void List_Debug_Print(Node*);

Node *List_Load_From_File(char *filename, int *status /*-1 for error*/) {
    FILE* fptr = fopen(filename, "rb"); //open bin file (read)
    if (!fptr) {
        printf ("fopen error\n");
        return NULL; //return NULL
    }

    // if (fseek(fptr, 0, SEEK_END) != 0) {
    //     printf ("can't find EOF\n");
    //     fclose(fptr);
    // }

    int size = ftell(fptr) / sizeof(long); //gets current read position

    Node *head = NULL;
    Node *tail = NULL;
    long val;

    while (fread(&val, sizeof(long), 1, fptr) == 1) {
        Node *new_node = malloc(sizeof(Node));
        if (!new_node) {
            printf("malloc error\n");
            fclose(fptr);
            *status = -1;
            return NULL;
        }

        new_node->value = val;
        new_node->next = NULL;

        if (!head) { //if first node
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    fclose(fptr);
    *status = 0;
    List_Debug_Print(head);

    return head;
}

//debug helper
static void List_Debug_Print(Node *head) {
    Node *curr = head;
    int idx = 0;

    printf("Linked list contents:\n");
    while (curr != NULL) {
        printf("[%d] %ld\n", idx, curr->value);
        curr = curr->next;
        idx ++;
    }

    if (idx == 0) {
        printf ("no elements\n");
    }
}