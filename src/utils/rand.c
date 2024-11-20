#include "rand.h"
#include <stdlib.h>
#include <time.h>

void RandZ_Init() {
    srand(time(NULL)); // Seed random number generator
}

unsigned int RandZ (unsigned int max_value) {
    if (max_value == 0) return 0;
    return (rand() % max_value + 1); // Return random number between 1 and max_value
}
