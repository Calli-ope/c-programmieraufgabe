#include "seq.h"

int main() {    
    FILE* log_file = fopen(LOG_FILE, "w");
    
    double duration = 0.;
    clock_t start, end = 0;
    
    // Liste generieren
    Node* list = Gen(NUM_NODES);
    
    // Liste vor Sortierung ausgeben
    //printf("Unsortierte Liste:\n");
    //ListOut(list, 0, NUM_NODES);
    
    start = clock();

    // Liste sortieren
    Sort(&list);

    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;

    // Ausgabe in Log-Datei
    fprintf(log_file, "Anzahl der Knoten: %d\n", NUM_NODES);
    fprintf(log_file, "Dauer der Sortierung: %f Sekunden\n", duration);

    fclose(log_file);

    // Liste nach Sortierung ausgeben
    //printf("Sortierte Liste:\n");
    //ListOut(list, 0, NUM_NODES);

    ListFree(list);

    return 0;
}
