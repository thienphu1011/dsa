#include <iostream>
#include <vector>

using namespace std;

struct SortStats {
    long long comparisons;
    long long moves;
};

void insertionSort(vector<int> &a, SortStats &stats) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int key = a[i];
        stats.moves++;
        int j = i - 1;
        while (j >= 0) {
            stats.comparisons++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                stats.moves++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
        stats.moves++;
    }
}

void selectionSort(vector<int> &a, SortStats &stats) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            stats.comparisons++;
            if (a[j] < a[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(a[i], a[minIdx]);
            stats.moves += 3;
        }
    }
}

void bubbleSort(vector<int> &a, SortStats &stats) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            stats.comparisons++;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                stats.moves += 3;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int partition(vector<int> &a, int low, int high, SortStats &stats) {
    int mid = low + (high - low) / 2;
    swap(a[mid], a[high]);
    stats.moves += 3;

    int pivot = a[high];
    stats.moves++;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats.comparisons++;
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
            stats.moves += 3;
        }
    }
    swap(a[i + 1], a[high]);
    stats.moves += 3;
    return i + 1;
}

void quickSortHelper(vector<int> &a, int low, int high, SortStats &stats) {
    if (low < high) {
        int pi = partition(a, low, high, stats);
        quickSortHelper(a, low, pi - 1, stats);
        quickSortHelper(a, pi + 1, high, stats);
    }
}

void quickSort(vector<int> &a, SortStats &stats) {
    if (!a.empty()) {
        quickSortHelper(a, 0, a.size() - 1, stats);
    }
}

void merge(vector<int> &a, vector<int> &temp, int left, int mid, int right, SortStats &stats) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        stats.comparisons++;
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
        stats.moves++;
    }

    while (i <= mid) {
        temp[k++] = a[i++];
        stats.moves++;
    }

    while (j <= right) {
        temp[k++] = a[j++];
        stats.moves++;
    }

    for (i = left; i <= right; i++) {
        a[i] = temp[i];
        stats.moves++;
    }
}

void mergeSortHelper(vector<int> &a, vector<int> &temp, int left, int right, SortStats &stats) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(a, temp, left, mid, stats);
        mergeSortHelper(a, temp, mid + 1, right, stats);
        merge(a, temp, left, mid, right, stats);
    }
}

void mergeSort(vector<int> &a, SortStats &stats) {
    if (a.size() <= 1) return;
    vector<int> temp(a.size());
    mergeSortHelper(a, temp, 0, a.size() - 1, stats);
}

void heapify(vector<int> &a, int n, int i, SortStats &stats) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        stats.comparisons++;
        if (a[left] > a[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        stats.comparisons++;
        if (a[right] > a[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        stats.moves += 3;
        heapify(a, n, largest, stats);
    }
}

void heapSort(vector<int> &a, SortStats &stats) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i, stats);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        stats.moves += 3;
        heapify(a, i, 0, stats);
    }
}

int nextRandom(unsigned int &seed) {
    seed = seed * 1103515245u + 12345u;
    return (seed / 65536u) % 32768u;
}

int main() {
    int n;
    cout << "Enter array size: ";
    if (!(cin >> n) || n <= 0) {
        n = 5000;
        cout << n << endl;
    }

    vector<int> original(n);
    unsigned int seed = 42;
    for (int i = 0; i < n; i++) {
        original[i] = nextRandom(seed);
    }

    vector<int> a;
    SortStats stats;

    a = original;
    stats = {0, 0};
    insertionSort(a, stats);
    cout << "Insertion Sort -> Comparisons: " << stats.comparisons << ", Moves: " << stats.moves << ", Total Ops: " << (stats.comparisons + stats.moves) << endl;

    a = original;
    stats = {0, 0};
    selectionSort(a, stats);
    cout << "Selection Sort -> Comparisons: " << stats.comparisons << ", Moves: " << stats.moves << ", Total Ops: " << (stats.comparisons + stats.moves) << endl;

    a = original;
    stats = {0, 0};
    bubbleSort(a, stats);
    cout << "Bubble Sort    -> Comparisons: " << stats.comparisons << ", Moves: " << stats.moves << ", Total Ops: " << (stats.comparisons + stats.moves) << endl;

    a = original;
    stats = {0, 0};
    quickSort(a, stats);
    cout << "Quick Sort     -> Comparisons: " << stats.comparisons << ", Moves: " << stats.moves << ", Total Ops: " << (stats.comparisons + stats.moves) << endl;

    a = original;
    stats = {0, 0};
    mergeSort(a, stats);
    cout << "Merge Sort     -> Comparisons: " << stats.comparisons << ", Moves: " << stats.moves << ", Total Ops: " << (stats.comparisons + stats.moves) << endl;

    a = original;
    stats = {0, 0};
    heapSort(a, stats);
    cout << "Heap Sort      -> Comparisons: " << stats.comparisons << ", Moves: " << stats.moves << ", Total Ops: " << (stats.comparisons + stats.moves) << endl;

    return 0;
}
