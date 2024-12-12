#include "par.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FILE* log_file = NULL;

typedef struct {
    Node* sublist_head;
    int thread_id;
} ThreadData;

void* ThrdFunc(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    
    double duration = 0.;
    clock_t start, end = 0;
    start = clock();

    // Subliste sortieren
    Sort(&data->sublist_head);

    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    //printf("\nThread %d nach Sort\n", data->thread_id);
    //ListOut(data->sublist_head, 0, NUM_NODES);

    pthread_mutex_lock(&mutex);
    fprintf(log_file, "ID des Threads: %d\n", data->thread_id);
    fprintf(log_file, "Dauer der Thread-Sortierung: %f Sekunden\n", duration);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    log_file = fopen(LOG_FILE, "w");
    
    Node* current = NULL;
    int remaining_nodes = NUM_NODES;
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    double duration = 0.;
    clock_t start, end = 0;
    
    // Liste generieren
    Node* list = Gen(NUM_NODES);
    Node** sublists = malloc(sizeof(Node*) * NUM_THREADS);


    // Liste vor Sortierung ausgeben
    //printf("Unsortierte Liste:\n");
    //ListOut(list, 0, NUM_NODES);

    start = clock();

    // Liste in Sublisten aufteilen
    current = list;
    for (int i = 0; i < NUM_THREADS; i++) {
        sublists[i] = current;
        int nodes_per_thread = remaining_nodes / (NUM_THREADS - i);

        // Ende der Subliste finden
        for (int j = 1; j < nodes_per_thread && current != NULL; j++) {
            current = current->next;
        }

        // Sublisten trennen
        if (current != NULL) {
            Node* next = current->next;
            current->next = NULL;
            if (next != NULL) {
                next->prev = NULL;
            }
            current = next;
        }
        remaining_nodes -= nodes_per_thread;
    }

    // Threads erstellen 
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].sublist_head = sublists[i];
        thread_data[i].thread_id = i + 1;
        pthread_create(&threads[i], NULL, ThrdFunc, &thread_data[i]);
    }

    // Threads zusammenführen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sublisten zu gemeinsamer Liste zusammenführen
    list = thread_data[0].sublist_head;

    for (int i = 1; i < NUM_THREADS; i++) {
        Node* list1 = list;
        Node* list2 = thread_data[i].sublist_head;

        Node dummy;
        Node* tail = &dummy;
        dummy.next = NULL;

        while (list1&&list2) {
            if (list1->data <= list2->data) {
                tail->next = list1;
                list1->prev = tail;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2->prev = tail;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // Rest anhängen
        if (list1) {
            tail->next = list1;
            list1->prev = tail;
        } else if (list2) {
            tail->next = list2;
            list2->prev = tail;
        }

        list = dummy.next;
        if (list) {
            list->prev = NULL;
        }
    }

    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    // Liste nach dem Sortieren ausgeben
    //printf("Sortierte Liste:\n");
    //ListOut(list, 0, NUM_NODES);

    // Ausgabe in Log-Datei
    fprintf(log_file, "\nAnzahl der Knoten: %d\n", NUM_NODES);
    fprintf(log_file, "Dauer der Gesamt-Sortierung: %f Sekunden\n", duration);

    fclose(log_file);
    ListFree(list);
    free(sublists);

    return 0;
}
