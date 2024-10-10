#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 10000

void bubblesort(int array[], const int n);
void quickSort(int arr[], int low, int high);
void heapSort(int arr[], int n);
void swap(int* a, int* b);
int partition (int arr[], int low, int high);
void printArray(const int array[], const int n);
void selectionSort(int array[], int n);

// Helper function to calculate time
void printDuration(clock_t start, clock_t end, const char* algo, const char* arrayType) {
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("%s on %s time elapsed: %.2f ms\n", algo, arrayType, duration);
}

int main() {
    int i;
    srand(time(0));

    // Stack-based array
    int number[ARRAYSIZE];

    // Heap-based array
    int* pNumber = (int*) malloc(sizeof(int) * ARRAYSIZE);
    if (pNumber == NULL) {
        printf("Error allocating memory for heap array\n");
        return -1;
    }

    // Stack - Selection Sort
    for (i = 0; i < ARRAYSIZE; i++) {
        number[i] = rand();
    }
    clock_t start = clock();
    selectionSort(number, ARRAYSIZE);
    clock_t end = clock();
    printDuration(start, end, "Selection sort", "stack");

    // Stack - Bubble Sort
    for (i = 0; i < ARRAYSIZE; i++) {
        number[i] = rand();
    }
    start = clock();
    bubblesort(number, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Bubble sort", "stack");

    // Stack - Quick Sort
    for (i = 0; i < ARRAYSIZE; i++) {
        number[i] = rand();
    }
    start = clock();
    quickSort(number, 0, ARRAYSIZE - 1);
    end = clock();
    printDuration(start, end, "Quick sort", "stack");

    // Heap - Selection Sort
    for (i = 0; i < ARRAYSIZE; i++) {
        pNumber[i] = rand();
    }
    start = clock();
    selectionSort(pNumber, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Selection sort", "heap");

    // Heap - Bubble Sort
    for (i = 0; i < ARRAYSIZE; i++) {
        pNumber[i] = rand();
    }
    start = clock();
    bubblesort(pNumber, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Bubble sort", "heap");

    // Heap - Quick Sort
    for (i = 0; i < ARRAYSIZE; i++) {
        pNumber[i] = rand();
    }
    start = clock();
    quickSort(pNumber, 0, ARRAYSIZE - 1);
    end = clock();
    printDuration(start, end, "Quick sort", "heap");

    // Heap - Heap Sort
    for (i = 0; i < ARRAYSIZE; i++) {
        pNumber[i] = rand();
    }
    start = clock();
    heapSort(pNumber, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Heap sort", "heap");

    free(pNumber);
    return 0;
}

void bubblesort(int array[], const int n) {
    int sorted, temp;
    do {
        sorted = 1;
        for (int i = 0; i < n - 1; i++) {
            if (array[i] > array[i + 1]) {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                sorted = 0;
            }
        }
    } while (!sorted);
}

// Selection sort implementation
void selectionSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }
        swap(&array[min_idx], &array[i]);
    }
}

// Quick sort and partition functions (already given)
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Swap utility
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heap sort implementation
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}
