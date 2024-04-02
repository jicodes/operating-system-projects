#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10 // Define the size of the array

typedef struct {
    int *arr;
    int startIdx;
    int endIdx;
} ThreadArgs;

// Insertion sort function for sorting a sublist
void insertionSort(int *arr, int startIdx, int endIdx) {
    for (int i = startIdx + 1; i <= endIdx; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= startIdx && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Merging function for merging two sorted subarrays
void merge(int *arr, int startIdx, int midIdx, int endIdx) {
    int i = startIdx, j = midIdx + 1, k = startIdx;
    int *tempArr = malloc((endIdx - startIdx + 1) * sizeof(int));

    while (i <= midIdx && j <= endIdx) {
        if (arr[i] <= arr[j]) {
            tempArr[k++] = arr[i++];
        } else {
            tempArr[k++] = arr[j++];
        }
    }

    while (i <= midIdx) {
        tempArr[k++] = arr[i++];
    }

    while (j <= endIdx) {
        tempArr[k++] = arr[j++];
    }

    for (int idx = startIdx; idx <= endIdx; idx++) {
        arr[idx] = tempArr[idx];
    }

    free(tempArr);
}

// Sorting thread function
void *sortThread(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    insertionSort(args->arr, args->startIdx, args->endIdx);
    pthread_exit(NULL);
}

// Merging thread function
void *mergeThread(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int midIdx = (args->startIdx + args->endIdx) / 2;
    merge(args->arr, args->startIdx, midIdx, args->endIdx);
    pthread_exit(NULL);
}

int main() {
    int arr[SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8}; // Array to be sorted

    pthread_t sortingThread1, sortingThread2, mergingThread;
    ThreadArgs args1, args2, mergeArgs;

    // Divide the array into two equal sublists
    args1.arr = arr;
    args1.startIdx = 0;
    args1.endIdx = SIZE / 2 - 1;
    args2.arr = arr;
    args2.startIdx = SIZE / 2;
    args2.endIdx = SIZE - 1;

    // Create two sorting threads
    pthread_create(&sortingThread1, NULL, sortThread, (void *)&args1);
    pthread_create(&sortingThread2, NULL, sortThread, (void *)&args2);

    // Wait for the sorting threads to finish
    pthread_join(sortingThread1, NULL);
    pthread_join(sortingThread2, NULL);

    // Merge the sorted subarrays
    mergeArgs.arr = arr;
    mergeArgs.startIdx = 0;
    mergeArgs.endIdx = SIZE - 1;
    pthread_create(&mergingThread, NULL, mergeThread, (void *)&mergeArgs);
    pthread_join(mergingThread, NULL);

    // Output the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}