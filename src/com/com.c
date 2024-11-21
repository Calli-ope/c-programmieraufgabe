#include "com.h"

Node* Reserve() {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node) {
        node->data = RandZ(20);
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

    // Find the maximum number to know the number of digits
    int max = 0;
    Node* node = head;
    while (node) {
        if (node->data > max) {
            max = node->data;
        }
        node = node->next;
    }

    // Do counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        // Initialize buckets
        Node* buckets[10] = {NULL};
        Node* tails[10] = {NULL};

        // Distribute nodes into buckets
        node = head;
        while (node) {
            Node* nextNode = node->next; // Save the next node
            node->next = NULL; // Disconnect the node

            int index = (node->data / exp) % 10;
            if (buckets[index] == NULL) {
                buckets[index] = tails[index] = node;
            } else {
                tails[index]->next = node;
                tails[index] = node;
            }
            node = nextNode;
        }

        // Concatenate buckets
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
