#include "seq.h"
#include <time.h>

int main() {
    FILE* log_file = fopen(LOG_FILE, "w");

    // Generate list
    Node* list = Gen(NUM_NODES);
    
    // Output list
    // ListOut(list, 0, NUM_NODES);
    
    // Start time
    clock_t start = clock();

    // Sort list
    Sort(&list);

    // End time
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    // Write number of nodes & duration to log file
    fprintf(log_file, "Number of nodes: %d\n", NUM_NODES);
    fprintf(log_file, "Duration: %f seconds\n", duration);

    fclose(log_file);

    // Output list
    ListOut(list, 0, NUM_NODES);

    // Free list
    ListFree(list);

    return 0;
}
