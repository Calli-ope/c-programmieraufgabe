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

    printf("Thread %d vor Sort\n", thread_data->thread_num);
    ListOut(thread_data->head, 0, 100);

    Sort(&thread_data->head);

    printf("Thread %d nach Sort\n", thread_data->thread_num);
    ListOut(thread_data->head, 0, 100);

    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&mutex);
    fprintf(log_file, "Number of Thread: %d\n", thread_data->thread_num);
    fprintf(log_file, "Duration: %f seconds\n", duration);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    // Define number of nodes
    int node_count = 20;

    // Generate list
    Node* list = Gen(node_count);
    Node** sublist = malloc(sizeof(Node*) * NUM_THREADS);

    // Output list
    printf("Unsorted list:\n");
    ListOut(list, 0, node_count);

    // Start time
    clock_t total_start = clock();

    // Split list
    Node* current = list;
    int remaining = node_count;

    for (int i = 0; i < NUM_THREADS; i++) {
        sublist[i] = current;
        int current_sublist_length = remaining / (NUM_THREADS - i);
        for (int j = 0; j < current_sublist_length - 1; j++) {
            if (current) {
                current = current->next;
            }
        }
        if (current) {
            Node* next = current->next;
            current->next = NULL;
            if (next) {
                next->prev = NULL;
            }
            current = next;
        }
        remaining -= current_sublist_length;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    log_file = fopen(LOG_FILE, "w");

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].head = sublist[i];
        thread_data[i].thread_num = i + 1;
        pthread_create(&threads[i], NULL, (void*)ThrdFunc, &thread_data[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge lists
    Node* merged_list = thread_data[0].head;

    for (int i = 1; i < NUM_THREADS; i++) {
        Node* l1 = merged_list;
        Node* l2 = thread_data[i].head;

        Node dummy;
        Node* tail = &dummy;
        dummy.next = NULL;

        // Merge l1 and l2
        while (l1&&l2) {
            if (l1->data <= l2->data) {
                tail->next = l1;
                l1->prev = tail;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2->prev = tail;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        // Append remaining nodes
        if (l1) {
            tail->next = l1;
            l1->prev = tail;
        } else if (l2) {
            tail->next = l2;
            l2->prev = tail;
        }

        // Update merged list
        merged_list = dummy.next;
        if (merged_list) {
            merged_list->prev = NULL;
        }
    }
    list = merged_list;

    // Output list
    printf("Sorted list:\n");
    ListOut(list, 0, node_count);

    // End time
    clock_t total_end = clock();

    double total_duration = (double)(total_end - total_start) / CLOCKS_PER_SEC;

    // Write number of nodes & duration to log file
    fprintf(log_file, "Number of nodes: %d\n", node_count);
    fprintf(log_file, "Duration: %f seconds\n", total_duration);

    fclose(log_file);

    // Free list
    ListFree(list);
    free(sublist);

    return 0;
}
