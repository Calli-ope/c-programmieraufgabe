#include "par.h"
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FILE* log_file;

typedef struct {
    Node* head;
    int thread_num;
} ThreadData;

void ThrdFunc(void* arg) {
    ThreadData* thread_data = (ThreadData*)arg;
    clock_t start = clock();

    Sort(thread_data->head);

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&mutex);
    fprintf(log_file, "Number of nodes: %d\n", thread_data->thread_num);
    fprintf(log_file, "Duration: %f seconds\n", duration);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    // Define number of nodes
    int node_count = 10000;

    // Generate list
    Node* list = Gen(node_count);
    Node** sublist = malloc(sizeof(Node*) * NUM_THREADS);
    int sublist_length = node_count / NUM_THREADS;

    // Split list
    Node* current = list;
    for (int i = 0; i < NUM_THREADS; i++) {
        sublist[i] = current;
        for (int j = 0; j < sublist_length - 1; j++) {
            if (current) {
                current = current->next;
            }
        }
        if (current) {
            Node* next = current->next;
            if (next) {
                next->prev = NULL;
            }
            current->next = NULL;
            current = next;
        }
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    log_file = fopen(LOG_FILE, "w");
    
    // Start time
    clock_t total_start = clock();

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].head = sublist[i];
        thread_data[i].thread_num = i + 1;
        pthread_create(&threads[i], NULL, ThrdFunc, &thread_data[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge lists
    for (int i = 1; i < NUM_THREADS; i++) {
        Node* last = sublist[i - 1];
        while (last->next) {
            last = last->next;
        }
        last->next = sublist[i];
        sublist[i]->prev = last;
    }
 
    // End time
    clock_t total_end = clock();

    double total_duration = (double)(total_end - total_start) / CLOCKS_PER_SEC;

    // Write duration to log file
    fprintf(log_file, "Number of nodes: %d\n", node_count);
    fprintf(log_file, "Duration: %f seconds\n", total_duration);

    fclose(log_file);

    // Free list
    ListFree(list);
    free(sublist);

    return 0;
}
