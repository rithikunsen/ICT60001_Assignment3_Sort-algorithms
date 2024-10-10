#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 10000

void bubbleSort(int array[], const int n);
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

/**
 * Print Duration
 * Calculates and prints the duration of a sorting algorithm, updating the `results` array.
 *
 * @param start The starting clock time.
 * @param end The ending clock time.
 * @param algo The name of the sorting algorithm.
 * @param arrayType The type of array sorted.
 * @param results An array to store sorting results.
 * @param index A pointer to the current index in the results array.
 *
 * Computes the elapsed time in milliseconds, prints it,
 * and updates the `results` array with the algorithm name, array type, and duration.
 */
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

    printf("\n"
    "*********************************************************\n"
        "Name: Rithikun Sen\n"
        "ID: 103800533\n"
        "*********************************************************\n");

    // Stack - Selection Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    clock_t start = clock();
    selectionSort(number, ARRAYSIZE);
    clock_t end = clock();
    printDuration(start, end, "Selection sort", "stack", results, &index);

    // Stack - Bubble Sort
    for (i = 0; i < ARRAYSIZE; i++) number[i] = rand();
    start = clock();
    bubbleSort(number, ARRAYSIZE);
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
    bubbleSort(pNumber, ARRAYSIZE);
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
    printf("\n*********************************************************"
           "\nSummarized Test Report Sorted By Time Taken (Descending):\n"
           "*********************************************************\n");
    for (i = 0; i < index; i++) {
        printf("%s on %s took %.2f ms\n", results[i].sortName, results[i].arrayType, results[i].duration);
    }
    return 0;
}

/**
 * Bubble Sort
 *
 * https://www.geeksforgeeks.org/bubble-sort-algorithm/
 * Author: Geekforgeeks
 * Last Updated: 06 Oct, 2024
 *
 * Implements the bubble sort algorithm, which repeatedly steps through the array,
 * compares adjacent elements, and swaps them if they are out of order until sorted.
 *
 * @param array The array to be sorted.
 * @param n The number of elements in the array.
 *
 * The algorithm "bubbles" larger elements to the end with each pass,
 * continuing until no swaps are needed.
 */
void bubbleSort(int array[], const int n) {
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
    } while (sorted == 0);
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


/**
 * Quick Sort
 *
 * https://www.geeksforgeeks.org/quick-sort-algorithm/
 * Author: Geeksforgeeks
 * Last Updated: 03 Oct, 2024
 *
 * Implements the quick sort algorithm using a divide-and-conquer approach.
 * It selects a pivot, partitions the array into elements smaller and larger
 * than the pivot, and recursively sorts the subarrays.
 *
 * @param arr The array to be sorted.
 * @param low The starting index of the subarray to be sorted.
 * @param high The ending index of the subarray to be sorted.
 *
 * Recursively sorts elements around the pivot until the entire array is sorted.
 */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/**
 * Partition Function
 *
 * https://www.geeksforgeeks.org/quick-sort-algorithm/
 * Author: Geeksforgeeks
 * Last Updated: 03 Oct, 2024
 *
 * Implements the partitioning step of QuickSort by selecting the last element as the pivot.
 * It rearranges the array so that elements smaller than the pivot are on the left and
 * larger ones on the right, then returns the pivot's index.
 *
 * @param arr The array to be partitioned.
 * @param low The starting index of the subarray to be partitioned.
 * @param high The ending index of the subarray to be partitioned, where the pivot is located.
 * @return The index of the pivot element after partitioning.
 *
 * The function iterates through the array, swaps elements, and places the pivot correctly.
 */
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

/**
 * Heapify
 *
 * https://www.geeksforgeeks.org/heap-sort/
 * Author: Geeksforgeeks
 * Last Updated: 28 Sep, 2024
 *
 * Ensures that the binary tree (or sub-tree) rooted at index `i` satisfies the
 * max heap property, where the parent node is greater than or equal to its children.
 *
 * @param arr The array representing the heap.
 * @param n The size of the heap.
 * @param i The index of the current node to heapify.
 *
 * The function checks if the node at index `i` is larger than its children;
 * if not, it swaps with the largest child and recursively heapifies the affected sub-tree.
 */
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

/**
 * Heap Sort
 *
 * https://www.geeksforgeeks.org/heap-sort/
 * Author: Geeksforgeeks
 * Last Updated: 28 Sep, 2024
 *
 * Implements the heap sort algorithm by building a max heap and repeatedly
 * extracting the largest element to sort the array.
 *
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 *
 * The function builds a max heap using `heapify`, then swaps the root with
 * the last element, reduces the heap size, and restores the heap property
 * by calling `heapify`.
 */
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/**
 * Get Maximum
 *
 * https://www.geeksforgeeks.org/radix-sort/
 * Author: Geeksforgeeks
 * Last Updated: 29 Aug, 2024
 *
 * This helper function finds and returns the maximum value in the array, which is used
 * by radix sort to determine the number of digits in the largest number.
 *
 * @param array The array to find the maximum value from.
 * @param n The number of elements in the array.
 * @return The maximum value in the array.
 */
int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max)
            max = array[i];
    }
    return max;
}

/**
 * Count Sort for Radix
 *
 * https://www.geeksforgeeks.org/radix-sort/
 * Author: Geeksforgeeks
 * Last Updated: 29 Aug, 2024
 *
 * A stable counting sort used by radix sort to sort an array based on a specific digit
 * defined by the exponent `exp`.
 *
 * @param array The array to be sorted.
 * @param n The number of elements in the array.
 * @param exp The exponent representing the current digit position (1 for units, 10 for tens, etc.).
 *
 * The function counts occurrences of each digit (0-9) at the current position and
 * rearranges the elements accordingly.
 */
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

/**
 * Radix Sort
 *
 * https://www.geeksforgeeks.org/radix-sort/
 * Author: Geeksforgeeks
 * Last Updated: 29 Aug, 2024
 *
 * A sorting algorithm that processes each digit of the array's numbers from least to
 * most significant, using counting sort for each digit.
 *
 * @param array The array to be sorted.
 * @param n The number of elements in the array.
 *
 * The function identifies the maximum number to determine the number of digits and
 * calls `countSortRadix` to sort the array digit by digit.
 */
void radixSort(int array[], int n) {
    int max = getMax(array, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSortRadix(array, n, exp);
}

/**
 * Shell Sort
 *
 * https://www.geeksforgeeks.org/shell-sort/
 * Author: Geeksforgeeks
 * Last Updated: 11 Jul, 2024
 *
 * An optimized insertion sort algorithm that uses a gap to compare and swap elements,
 * reducing the gap progressively until it reaches 1, where it acts like insertion sort.
 *
 * @param array The array to be sorted.
 * @param n The number of elements in the array.
 *
 * The function begins with an initial gap (usually half the array size) and performs
 * insertion sorts with that gap, progressively decreasing it for faster overall sorting.
 */
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

/**
 * Merge Function
 *
 * https://www.geeksforgeeks.org/merge-sort/
 * Author: Geeksforgeeks
 * Last Updated: 17 Sep, 2024
 *
 * Merges two sorted subarrays (`array[l..m]` and `array[m+1..r]`) into one sorted subarray.
 *
 * @param array The array containing the subarrays to be merged.
 * @param l The starting index of the left subarray.
 * @param m The middle index, which separates the left and right subarrays.
 * @param r The ending index of the right subarray.
 *
 * The function copies the subarrays into temporary arrays and merges them back
 * into the original array in sorted order.
 */
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

/**
 * Merge Sort
 *
 * https://www.geeksforgeeks.org/merge-sort/
 * Author: Geeksforgeeks
 * Last Updated: 17 Sep, 2024
 *
 * Implements the merge sort algorithm by dividing the array into two halves,
 * recursively sorting each half, and merging the sorted halves.
 *
 * @param array The array to be sorted.
 * @param l The left index of the subarray to be sorted.
 * @param r The right index of the subarray to be sorted.
 *
 * The function recursively divides the array until each subarray has one element,
 * then uses the `merge` function to combine them back together.
 */
void mergeSort(int array[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}

// Utility function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
