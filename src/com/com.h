#include "../utils/rand.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Global variables
#define NUM_NODES 800

// Declarations
Node* Gen(int anzahl);
Node* Reserve();
void Sort(Node** headRef);
void ListOut(Node* head, int von, int bis);
void ListFree(Node* head);
