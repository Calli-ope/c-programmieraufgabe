#include "../utils/rand.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Global variables


// Declarations
Node* Gen(int anzahl);
Node* Reserve();
void Sort(Node* head);
void ListOut(Node* head, int von, int bis);
void ListFree(Node* head);
