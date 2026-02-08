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
    //find size
    int size = 0;
    //traverses until n=NULL
    for (Node *n = list; n != NULL; n = n->next) {
        size ++;
    }

    //sort
    for (int gap = size / 2; gap > 0; gap /= 2) {
        //move ith ptr gap nodes ahead
        Node *i_prev = NULL;
        Node *i_node = list; //starts at head
        for (int i = 0; i < gap; i ++) {
            i_prev = i_node;
            i_node = i_node->next;
        }
        //gapped insertion sort
        while (i_node) {
            Node *curr_prev = i_prev;
            Node *curr = i_node;
            //traverse backwards by gap
            while (curr_prev) {
                //find node gap steps behind curr
                Node *gap_prev = curr_prev;
                Node *gap_node = curr_prev->next;

                //compare
                (*n_comp) ++;
                if (gap_node->value <= curr->value) {
                    break;
                }

                //bubble back
                Swap_Adjacent(&list, gap_prev);

                //move back
                curr_prev = gap_prev;
            }
            i_prev = i_node;
            i_node = i_node->next;
        }
    }
    List_Debug_Print(list);
    return list;
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