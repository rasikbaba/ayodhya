#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

int frames[MAX_FRAMES];
int pages[MAX_PAGES];
int nFrames, nPages;

void displayFrames() {
    printf("Frames: ");
    for (int i = 0; i < nFrames; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

void initializeFrames() {
    for (int i = 0; i < nFrames; i++) {
        frames[i] = -1;
    }
}

int isInFrames(int page) {
    for (int i = 0; i < nFrames; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

int getLRUIndex(int page) {
    int idx = 0;
    for (int i = 1; i < nFrames; i++) {
        if (pages[frames[i]] < pages[frames[idx]])
            idx = i;
    }
    return idx;
}

int getOptimalIndex(int start) {
    int idx = -1, farthest = start;
    for (int i = 0; i < nFrames; i++) {
        int j;
        for (j = start; j < nPages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    idx = i;
                }
                break;
            }
        }
        if (j == nPages)
            return i;
    }
    return (idx == -1) ? 0 : idx;
}

void FCFS() {
    initializeFrames();
    int pageFaults = 0, frameIndex = 0;
    for (int i = 0; i < nPages; i++) {
        if (!isInFrames(pages[i])) {
            frames[frameIndex] = pages[i];
            frameIndex = (frameIndex + 1) % nFrames;
            pageFaults++;
            displayFrames();
        }
    }
    printf("Total Page Faults (FCFS): %d\n", pageFaults);
}

void LRU() {
    initializeFrames();
    int pageFaults = 0;
    for (int i = 0; i < nPages; i++) {
        if (!isInFrames(pages[i])) {
            int idx = getLRUIndex(i);
            frames[idx] = pages[i];
            pageFaults++;
            displayFrames();
        }
    }
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void Optimal() {
    initializeFrames();
    int pageFaults = 0;
    for (int i = 0; i < nPages; i++) {
        if (!isInFrames(pages[i])) {
            int idx = getOptimalIndex(i + 1);
            frames[idx] = pages[i];
            pageFaults++;
            displayFrames();
        }
    }
    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

int main() {
    printf("Enter the number of frames: ");
    scanf("%d", &nFrames);
    if (nFrames <= 0 || nFrames > MAX_FRAMES) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    printf("Enter the number of pages: ");
    scanf("%d", &nPages);
    if (nPages <= 0 || nPages > MAX_PAGES) {
        printf("Invalid number of pages.\n");
        return 1;
    }

    printf("Enter the page sequence: ");
    for (int i = 0; i < nPages; i++) {
        scanf("%d", &pages[i]);
    }

    FCFS();
    LRU();
    Optimal();

    return 0;
}
