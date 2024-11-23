#include "par.h"
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
FILE* log_file;

typedef struct {
    Node* sublist_head;
    int thread_id;
} ThreadData;

void ThrdFunc(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    clock_t start_time = clock();

    /*printf("Thread %d vor Sort\n", data->thread_id);
    ListOut(data->sublist_head, 0, NUM_NODES);*/

    // Sort sublist
    Sort(&data->sublist_head);

    printf("Thread %d nach Sort\n", data->thread_id);
    ListOut(data->sublist_head, 0, NUM_NODES);

    clock_t end_time = clock();
    double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    pthread_mutex_lock(&mutex);
    fprintf(log_file, "Number of Thread: %d\n", data->thread_id);
    fprintf(log_file, "Duration: %f seconds\n", duration);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    // Generate list
    Node* list = Gen(NUM_NODES);
    Node** sublists = malloc(sizeof(Node*) * NUM_THREADS);

    // Output list
    /*printf("Unsorted list:\n");
    ListOut(list, 0, NUM_NODES);*/

    // Start time
    clock_t total_start = clock();

    // Split list
    Node* current = list;
    int remaining_nodes = NUM_NODES;

    for (int i = 0; i < NUM_THREADS; i++) {
        sublists[i] = current;
        int nodes_per_thread = remaining_nodes / (NUM_THREADS - i);

        // Find end of current sublist
        for (int j = 1; j < nodes_per_thread && current != NULL; j++) {
                current = current->next;
        }

        // Disconnect sublist
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

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    log_file = fopen(LOG_FILE, "w");

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].sublist_head = sublists[i];
        thread_data[i].thread_id = i + 1;
        pthread_create(&threads[i], NULL, ThrdFunc, &thread_data[i]);
    }

    // Wait for threads to complete and join them
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Merge sorted sublists
    Node* merged_list = thread_data[0].sublist_head;

    for (int i = 1; i < NUM_THREADS; i++) {
        Node* list1 = merged_list;
        Node* list2 = thread_data[i].sublist_head;

        Node dummy;
        Node* tail = &dummy;
        dummy.next = NULL;

        // Merge list1 and list2
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

        // Append remaining nodes
        if (list1) {
            tail->next = list1;
            list1->prev = tail;
        } else if (list2) {
            tail->next = list2;
            list2->prev = tail;
        }

        // Update head of merged list
        merged_list = dummy.next;
        if (merged_list) {
            merged_list->prev = NULL;
        }
    }

    // Update main list to point to merged list
    list = merged_list;

    // Output list
    printf("Sorted list:\n");
    ListOut(list, 0, NUM_NODES);

    // End time
    clock_t total_end = clock();
    double total_duration = (double)(total_end - total_start) / CLOCKS_PER_SEC;

    // Write number of nodes & duration to log file
    fprintf(log_file, "Number of nodes: %d\n", NUM_NODES);
    fprintf(log_file, "Duration: %f seconds\n", total_duration);

    fclose(log_file);

    // Free list
    ListFree(list);
    free(sublists);

    return 0;
}
