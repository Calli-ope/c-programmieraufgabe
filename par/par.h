#include <pthread.h>
#include <time.h>
#include "../com/com.h"

// Name der Datei, in die die Log-Einträge geschrieben werden
#define LOG_FILE "par.log"
// Anzahl der Threads, die parallel laufen sollen
#define NUM_THREADS 8