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

// Bubble Sort
void Sort(Node* head) {
    Node* i = head;
    while (i) {
        Node* j = i->next;
        while (j) {
            if (i->data > j->data) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
            j = j->next;
        }
        i = i->next;
    }
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
    printf("\n");
}

void ListFree(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}
