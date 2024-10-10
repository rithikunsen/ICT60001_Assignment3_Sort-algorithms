#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 10000

void bubblesort(int array[], const int n);
void quickSort(int arr[], int low, int high);
void heapSort(int arr[], int n);
void radixSort(int array[], int n);
void shellSort(int array[], int n);
void selectionSort(int array[], int n);
void mergeSort(int array[], int l, int r);
void swap(int* a, int* b);
int partition(int * arr, int low, int high);

struct SortResult {
    char sortName[50];
    char arrayType[10];
    double duration;
};

void printDuration(clock_t start, clock_t end, const char* algo, const char* arrayType, struct SortResult results[], int *index) {
    double duration = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("%s on %s time elapsed: %.2f ms\n", algo, arrayType, duration);
    sprintf(results[*index].sortName, "%s", algo);
    sprintf(results[*index].arrayType, "%s", arrayType);
    results[*index].duration = duration;
    (*index)++;
}

void sortResultsByTime(struct SortResult results[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (results[j].duration < results[j + 1].duration) {
                struct SortResult temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }
}

// Merge Sort implementation
void merge(int array[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}

int main() {
    int i, index = 0;
    srand(time(0));

    // Stack-based array
    int number[ARRAYSIZE];

    // Heap-based array
    int* pNumber = (int*) malloc(sizeof(int) * ARRAYSIZE);
    if (pNumber == NULL) {
        printf("Error allocating memory for heap array\n");
        return -1;
    }

    struct SortResult results[14];  // Adjusted size to accommodate all sorts

    // Stack - Selection Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    clock_t start = clock();
    selectionSort(number, ARRAYSIZE);
    clock_t end = clock();
    printDuration(start, end, "Selection sort", "stack", results, &index);

    // Stack - Bubble Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    start = clock();
    bubblesort(number, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Bubble sort", "stack", results, &index);

    // Stack - Quick Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    start = clock();
    quickSort(number, 0, ARRAYSIZE - 1);
    end = clock();
    printDuration(start, end, "Quick sort", "stack", results, &index);

    // Stack - Radix Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    start = clock();
    radixSort(number, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Radix sort", "stack", results, &index);

    // Stack - Shell Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    start = clock();
    shellSort(number, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Shell sort", "stack", results, &index);

    // Stack - Merge Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    start = clock();
    mergeSort(number, 0, ARRAYSIZE - 1);
    end = clock();
    printDuration(start, end, "Merge sort", "stack", results, &index);

    // Heap - Bubble Sort
    for (i = 0; i < ARRAYSIZE; i++) pNumber[i] = rand();
    start = clock();
    bubblesort(pNumber, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Bubble sort", "heap", results, &index);

    // Heap - Quick Sort
    for (i = 0; i < ARRAYSIZE; i++) pNumber[i] = rand();
    start = clock();
    quickSort(pNumber, 0, ARRAYSIZE - 1);
    end = clock();
    printDuration(start, end, "Quick sort", "heap", results, &index);

    // Heap - Heap Sort
    for (i = 0; i < ARRAYSIZE; i++) pNumber[i] = rand();
    start = clock();
    heapSort(pNumber, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Heap sort", "heap", results, &index);

    // Heap - Radix Sort
    for (i = 0; i < ARRAYSIZE; i++) pNumber[i] = rand();
    start = clock();
    radixSort(pNumber, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Radix sort", "heap", results, &index);

    // Heap - Shell Sort
    for (i = 0; i < ARRAYSIZE; i++) pNumber[i] = rand();
    start = clock();
    shellSort(pNumber, ARRAYSIZE);
    end = clock();
    printDuration(start, end, "Shell sort", "heap", results, &index);

    // Heap - Merge Sort
    for (i = 0; i < ARRAYSIZE; i++) pNumber[i] = rand();
    start = clock();
    mergeSort(pNumber, 0, ARRAYSIZE - 1);
    end = clock();
    printDuration(start, end, "Merge sort", "heap", results, &index);

    free(pNumber);

    // Sort the results by time taken in descending order
    sortResultsByTime(results, index);

    printf("\nResults sorted by time taken (descending):\n");
    for (i = 0; i < index; i++) {
        printf("%s on %s took %.2f ms\n", results[i].sortName, results[i].arrayType, results[i].duration);
    }

    return 0;
}

// Implementing Bubble Sort
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

// Implementing Selection Sort
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


// Implementing Quick Sort
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

// Implementing Heap Sort and Heapify
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

// Implementing Radix Sort and Count Sort for Radix
int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

void countSortRadix(int array[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(array[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        array[i] = output[i];
}

void radixSort(int array[], int n) {
    int max = getMax(array, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSortRadix(array, n, exp);
}

// Implementing Shell Sort
void shellSort(int array[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = array[i];
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];
            array[j] = temp;
        }
    }
}

// Utility function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
