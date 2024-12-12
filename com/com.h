#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Anzahl der Knoten, die generiert und sortiert werden sollen
#define NUM_NODES 10000000

// Deklarationen
Node* Gen(int anzahl);
Node* Reserve();
void Sort(Node** headRef);
void ListOut(Node* head, int von, int bis);
void ListFree(Node* head);
unsigned int RandZ(unsigned char places);
