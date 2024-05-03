#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CYLINDERS 5000
#define REQUESTS 1000

void sort_array(int *ran_array, int size);
int sstf(int *ran_array, int size, int start);
int scan(int *ran_array, int size, int start);
int clook(int *ran_array, int size, int start);

int main(int argc, char *argv[]) {
    int i, start;
    int ran_array[REQUESTS];

    if (argc != 2) {
        printf("Usage: %s <starting_index>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    start = atoi(argv[1]);

    if (start < 0 || start >= CYLINDERS) {
        printf("Starting index must be between 0 and %d\n", CYLINDERS - 1);
        exit(EXIT_FAILURE);
    }

    // Generate random disk I/O requests
    for (i = 0; i < REQUESTS; i++) {
        ran_array[i] = rand() % CYLINDERS;
    }

    printf("Start index: %d, start value: %d\n\n", start, ran_array[start]);
    printf("SSTF head movements: %d\n", sstf(ran_array, REQUESTS, start));
    printf("SCAN head movements: %d\n", scan(ran_array, REQUESTS, start));
    printf("C-LOOK head movements: %d\n\n", clook(ran_array, REQUESTS, start));

    return 0;
}

// Sort the array of disk I/O requests
void sort_array(int *ran_array, int size) {
    int i, j, temp;
    for (i = 0; i < size; ++i) {
        for (j = i + 1; j < size; ++j) {
            if (ran_array[i] > ran_array[j]) {
                temp = ran_array[i];
                ran_array[i] = ran_array[j];
                ran_array[j] = temp;
            }
        }
    }
}

// Implementation of SSTF algorithm
int sstf(int *ran_array, int size, int start) {
    // Implementation
}

// Implementation of SCAN algorithm
int scan(int *ran_array, int size, int start) {
    // Implementation
}

// Implementation of C-LOOK algorithm
int clook(int *ran_array, int size, int start) {
    // Implementation
}
