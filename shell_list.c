#include <stdio.h>
#include <stdlib.h>
#include "shell_list.h"
#include "sequence.h"

static void List_Debug_Print(Node*);
static void Swap_Nodes(Node **, Node *, Node *, Node *, Node *);
static void Swap_Adjacent(Node **, Node *);
static Node* Get_Prev_Node(Node *, int);

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
        return list; //return empty list
    }
    *n_comp = 0; //number of comparisons
    Node *n1, *n2, *n3, *n4, *n5; //dummy nodes
    Node *idx1, *idx2; //location of first index
    int size = 0; //size of ll
    // int adj = 0; //number of adjacent swaps (debug)
    // int non_adj = 0; //number of non-adjacent swaps (debug)
    int seq_size; //size of 2p3q sequence

    //find size of ll
    for (Node *n = list; n != NULL; n = n->next) {
        size++;
    }

    //generate k-gap sequence
    long *gap_seq = Generate_2p3q_Seq(size, &seq_size);

    //real dummy head to protect head swaps
    Node dummy;
    dummy.next = list;
    Node *dummy_head = &dummy;
    int count = 0;

    //outer k-loop
    for (int gap = gap_seq[seq_size - 1]; count < seq_size; gap = gap_seq[seq_size - (1 + count)]) {
        int swapped = 1;
        int calc_gap = 1;
        count ++;

        //find gap index - 1
        idx2 = dummy_head;
        for (int i = 0; i < gap - 1; i++) {
            idx2 = idx2->next;
            calc_gap ++;
        }
        if (gap != calc_gap) {
            printf("GAP DIFFERENCE!\n");
        }
        // printf("[%d] %d\n", gap, calc_gap);

        //bubble sort of k-size "gap"
        while (swapped) {
            swapped = 0;

            //reset indices
            idx1 = dummy.next;
            //assign initial dummy pointers
            n1 = dummy_head;
            n2 = idx1;
            n3 = idx1->next;
            // n4 = n2;
            // for (int i = 0; i < gap - 1; i++) {
            //     n4 = n4->next;
            // }
            n4 = idx2;
            n5 = n4->next;

            //single bubble sort pass
            while (n5 != NULL) {
                int did_swap = 0;
                (*n_comp)++;
                //swap comparison
                if (n2->value > n5->value) {
                    swapped = 1;
                    did_swap = 1;
                    if (gap == 1) { //adjacent swap
                        n1->next = n5;
                        n2->next = n5->next;
                        n5->next = n2;
                        // adj++;
                    } else { //non-adjacent swap
                        Node *after5 = n5->next;
                        n1->next = n5;
                        n4->next = n2;
                        n5->next = n2->next;
                        n2->next = after5;
                        // non_adj++;
                    }
                }
                //advance dummy nodes
                if (!did_swap) {
                    n1 = n2;
                    n2 = n2->next;
                    if (!n2) break;
                    n3 = n2->next;

                    n4 = n4->next;
                    if (!n4) break;
                    n5 = n4->next;
                } else {
                    n1 = n5;
                    n2 = n5->next;
                    if (!n2) break;
                    n3 = n2->next;

                    if (gap == 1) {
                        n4 = n2;
                    }
                    n5 = n4->next;
                }
            }
        }
    }
    // List_Debug_Print(dummy.next);
    // printf("adj: %d non_adj: %d\n", adj, non_adj);
    printf("with %ld comparisons", n_comp);
    return dummy.next;
}

//debug helper
static void List_Debug_Print(Node *head) {
    Node *curr = head;
    Node *prev;
    int idx = 0;
    int err = 0;

    printf("Linked list contents:\n");
    while (curr != NULL) {
        printf("[%d] %ld\n", idx, curr->value);
        prev = curr;
        curr = curr->next;
        if (curr && prev) {
            if (prev->value > curr->value) {
                printf(" !!!\n");
                err = 1;
            }
        }  
        // printf("\n");
        idx ++;
    }

    if (err) {
        printf ("Error - out of order detected\n");
    }

    if (idx == 0) {
        printf ("no elements\n");
    }
}

