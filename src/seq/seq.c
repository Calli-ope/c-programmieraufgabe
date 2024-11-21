#include "seq.h"
#include <time.h>

int main() {
    // Define number of nodes
    int node_count = 1000000;

    FILE* log_file = fopen(LOG_FILE, "w");

    // Generate list
    Node* list = Gen(node_count);
    
    // Output list
    ListOut(list, 0, 1000000);
    
    // Start time
    clock_t start = clock();

    // Sort list
    Sort(list);

    // End time
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    // Write number of nodes & duration to log file
    fprintf(log_file, "Number of nodes: %d\n", node_count);
    fprintf(log_file, "Duration: %f seconds\n", duration);

    fclose(log_file);

    // Output list
    ListOut(list, 0, 1000000);

    // Free list
    ListFree(list);

    return 0;
}
