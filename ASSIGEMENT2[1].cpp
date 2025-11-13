#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// ------------------------------
// Problem 1: Deadlock Detection
// ------------------------------
void deadlockDetection() {
    int n, m;
    printf("\n--- Deadlock Detection Algorithm ---\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int **alloc = (int **)malloc(n * sizeof(int *));
    int **req = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        alloc[i] = (int *)malloc(m * sizeof(int));
        req[i] = (int *)malloc(m * sizeof(int));
    }

    int *avail = (int *)malloc(m * sizeof(int));
    bool *finish = (bool *)calloc(n, sizeof(bool));

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    bool progress = true;
    while (progress) {
        progress = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < m; j++) {
                    if (req[i][j] > avail[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    }

    bool deadlock = false;
    printf("\nProcesses in Deadlock: ");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = true;
        }
    }
    if (!deadlock) printf("None");
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(alloc[i]);
        free(req[i]);
    }
    free(alloc);
    free(req);
    free(avail);
    free(finish);
}

// --------------------------------------
// Problem 2: Belady's Anomaly (FIFO/LRU)
// --------------------------------------
bool searchPage(int key, int *frames, int frameCount) {
    for (int i = 0; i < frameCount; i++)
        if (frames[i] == key)
            return true;
    return false;
}

void beladyAnomaly() {
    printf("\n--- Belady's Anomaly (FIFO & LRU) ---\n");
    int n, capacity;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int *pages = (int *)malloc(n * sizeof(int));
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter frame size: ");
    scanf("%d", &capacity);

    // FIFO
    int *frames = (int *)malloc(capacity * sizeof(int));
    int frameCount = 0, front = 0;
    int pageFaultsFIFO = 0;
    for (int i = 0; i < n; i++) {
        if (!searchPage(pages[i], frames, frameCount)) {
            if (frameCount < capacity) {
                frames[frameCount++] = pages[i];
            } else {
                frames[front] = pages[i];
                front = (front + 1) % capacity;
            }
            pageFaultsFIFO++;
        }
    }

    // LRU
    int *framesLRU = (int *)malloc(capacity * sizeof(int));
    int *time = (int *)malloc(capacity * sizeof(int));
    int pageFaultsLRU = 0, count = 0, frameLRUCount = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < frameLRUCount; j++) {
            if (framesLRU[j] == pages[i]) {
                time[j] = ++count;
                found = true;
                break;
            }
        }
        if (!found) {
            if (frameLRUCount < capacity) {
                framesLRU[frameLRUCount] = pages[i];
                time[frameLRUCount++] = ++count;
            } else {
                int minTime = time[0], pos = 0;
                for (int j = 1; j < capacity; j++) {
                    if (time[j] < minTime) {
                        minTime = time[j];
                        pos = j;
                    }
                }
                framesLRU[pos] = pages[i];
                time[pos] = ++count;
            }
            pageFaultsLRU++;
        }
    }

    printf("\nFIFO Page Faults: %d", pageFaultsFIFO);
    printf("\nLRU Page Faults: %d\n", pageFaultsLRU);

    free(pages);
    free(frames);
    free(framesLRU);
    free(time);
}

// -----------------------------------------
// Problem 3: C-SCAN Disk Scheduling
// -----------------------------------------
int compareInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void cscanScheduling() {
    printf("\n--- C-SCAN Disk Scheduling ---\n");
    int n, head, diskSize;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int *requests = (int *)malloc(n * sizeof(int));
    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    int *left = (int *)malloc((n + 1) * sizeof(int));
    int *right = (int *)malloc((n + 1) * sizeof(int));
    int leftCount = 0, rightCount = 0;
    right[rightCount++] = diskSize - 1;
    left[leftCount++] = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[leftCount++] = requests[i];
        else if (requests[i] > head)
            right[rightCount++] = requests[i];
    }

    qsort(left, leftCount, sizeof(int), compareInt);
    qsort(right, rightCount, sizeof(int), compareInt);

    int distance = 0, cur = head;
    printf("\nSeek Sequence: ");
    for (int i = 0; i < rightCount; i++) {
        printf("%d ", right[i]);
        distance += abs(right[i] - cur);
        cur = right[i];
    }
    distance += (diskSize - 1 - head);
    cur = 0;
    for (int i = 0; i < leftCount; i++) {
        printf("%d ", left[i]);
        distance += abs(left[i] - cur);
        cur = left[i];
    }

    printf("\nTotal Seek Distance: %d\n", distance);

    free(requests);
    free(left);
    free(right);
}

// ------------------------------
// Main Menu
// ------------------------------
int main() {
    int choice;
    do {
        printf("\n====================================");
        printf("\nOS Algorithms Combined Menu");
        printf("\n1. Deadlock Detection");
        printf("\n2. Belady's Anomaly (FIFO & LRU)");
        printf("\n3. C-SCAN Disk Scheduling");
        printf("\n4. Exit");
        printf("\n====================================");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: deadlockDetection(); break;
            case 2: beladyAnomaly(); break;
            case 3: cscanScheduling(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}

