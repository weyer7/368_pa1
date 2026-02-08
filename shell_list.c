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
    // List_Debug_Print(head);

    return head;
}

int List_Save_To_File(char *filename, Node* list) {
    FILE* fptr = fopen(filename, "wb"); //open bin file (write)
    if (!fptr) {
        printf ("fopen error\n");
        return -1;
    }

    //write files into array
    Node *curr = list;
    int written = 0;
    fseek(fptr, 0, SEEK_SET); //reset fptr
    while (curr != NULL) {
        fwrite (&curr->value, sizeof(long), 1, fptr);
        curr = curr->next;
        written ++;
    }
    
    fclose (fptr);
    return written;
}

Node *List_Shellsort(Node *list, long *n_comp) {
    if (!list || !list->next) {
        return list; //nothing to sort
    }
    *n_comp = 0;
    Node dummy;
    dummy.next = list;

    int swapped;
    do {
        swapped = 0;
        Node *prev = &dummy;

        while (prev->next && prev->next->next) {
            (*n_comp) ++;
            if(prev->next->value > prev->next->next->value) {
                Swap_Adjacent(&dummy.next, prev);
                swapped = 1;
            } else {
                prev = prev->next;
            }
        }
    } while (swapped);

    List_Debug_Print(list);

    return dummy.next;
}

//adjacent node swap helper
void Swap_Adjacent(Node **head, Node *prev) {
    Node *a;
    Node *b;
    //determine A
    if (prev == NULL) {
        a = *head;
    } else {
        a = prev->next;
    }
    if (a == NULL || a->next == NULL) {
        return; //nothing to swap
    }
    b = a->next;
    //swap
    a->next = b->next;
    b->next = a;
    if (prev != NULL) {
        prev->next = b;
    } else {
        *head = b;
    }
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