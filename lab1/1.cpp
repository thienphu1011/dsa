#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>   

using namespace std;

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int partitionAlg(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionAlg(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int a[], int l, int m, int r) {
    vector<int> left(a + l, a + m + 1);
    vector<int> right(a + m + 1, a + r + 1);
    int i = 0, j = 0, k = l;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) a[k++] = left[i++];
        else a[k++] = right[j++];
    }
    while (i < left.size()) a[k++] = left[i++];
    while (j < right.size()) a[k++] = right[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}



void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; ++i) {
        dest[i] = source[i];
    }
}

void problem1(int originalArray[], int n) {
    cout << "LAB 1: PROBLEM 1 \n";
    
    int* arr = new int[n];
    clock_t start, end;

    copyArray(originalArray, arr, n);
    start = clock();
    insertionSort(arr, n);
    end = clock();
    cout << "Insertion Sort: " << double(end - start) / CLOCKS_PER_SEC << " s\n";

    copyArray(originalArray, arr, n);
    start = clock();
    selectionSort(arr, n);
    end = clock();
    cout << "Selection Sort: " << double(end - start) / CLOCKS_PER_SEC << " s\n";

    copyArray(originalArray, arr, n);
    start = clock();
    bubbleSort(arr, n);
    end = clock();
    cout << "Bubble Sort: " << double(end - start) / CLOCKS_PER_SEC << " s\n";

    copyArray(originalArray, arr, n);
    start = clock();
    quickSort(arr, 0, n - 1);
    end = clock();
    cout << "Quick Sort: " << double(end - start) / CLOCKS_PER_SEC << " s\n";

    copyArray(originalArray, arr, n);
    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    cout << "Merge Sort: " << double(end - start) / CLOCKS_PER_SEC << " s\n";

    

    delete[] arr;
    cout << "\n";
}



int main() {
    const int SIZE = 10000;
    int* originalArray = new int[SIZE];
    
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        originalArray[i] = rand() % 100000;
    }

    problem1(originalArray, SIZE);
    delete[] originalArray;
    return 0;
}