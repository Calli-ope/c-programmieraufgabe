#include "com.h"

Node* Reserve() {
    Node* node = (Node*)malloc(sizeof(Node));

    if (node) {
        node->data = RandZ(1+RandZ(2)%9);
        node->next = NULL;
        node->prev = NULL;
    }
    return node;
}

Node* Gen(int anzahl) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < anzahl; i++) {
        Node* node = Reserve();
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    return head;
}

// Radix Sort
void Sort(Node** headRef) {
    Node* head = *headRef;
    int max = 0;
    Node* node = head;

    // Finde das Maximum
    while (node) {
        if (node->data > max) {
            max = node->data;
        }
        node = node->next;
    }

    // Sortierung
    for (int exp = 1; max / exp > 0; exp *= 10) {
        // Buckets initialisieren
        Node* buckets[10] = {NULL};
        Node* tails[10] = {NULL};

        // Verteilung
        node = head;
        while (node) {
            Node* nextNode = node->next;
            node->next = NULL;

            int index = (node->data / exp) % 10;
            if (buckets[index] == NULL) {
                buckets[index] = tails[index] = node;
            } else {
                tails[index]->next = node;
                tails[index] = node;
            }
            node = nextNode;
        }

        // Bucket zusammenfügen
        head = NULL;
        Node* last = NULL;
        for (int i = 0; i < 10; i++) {
            if (buckets[i]) {
                if (head == NULL) {
                    head = buckets[i];
                    last = tails[i];
                } else {
                    last->next = buckets[i];
                    last = tails[i];
                }
            }
        }
    }
    *headRef = head;
}

void ListOut(Node* head, int von, int bis) {
    Node* node = head;
    int i = 0;

    // Parameter überprüfen, ob sie innerhalb des gültigen Bereichs liegen
    if (von < 1 || bis < 1 || von > NUM_NODES || bis > NUM_NODES) {
        // Wenn nicht, dann den gesamten Bereich ausgeben
        von = 1;
        bis = NUM_NODES;
    }

    // Liste ausgeben
    while (node) {
        if (i >= von && i <= bis) {
            printf("%d ", node->data);
        }
        node = node->next;
        i++;
    }
    printf("\n\n");
}

void ListFree(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

unsigned int RandZ (unsigned char places) // from 1 to 9 places = max 999 999 999
/*
    Parameter:
        places=0 for init,
        places=1..9 for generating a random number with given places.
        A false number of places will be corrected.
    Return value:
        An unsigned integer with given positions (0 - 999 999 999).
        The number of positions can be less if the number starts with 0.
    Calling RandZ(1+RandZ(2)%9) generates a random number
        with random number of positions.
    Calling RandZ(RandZ(9)) includes the random initialising.
*/
{
    unsigned char j=1;
    double d=0.;

    if (places)
    {
        if (places>9) places = 1 + places%9; // unsigned places cannot be <0
        d = ((double) time(NULL)) / rand();
        //  extract all positions to right of comma
        d = d - (unsigned int) d;
        // shift the positions to left
        while (d*=10, j<places) j++;
    }
    else
        srand(time(NULL));  //  if places == 0 then init
    return (unsigned int) d;  // unsigned int = xxx xxx xxx
}
