#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int> &a, int low, int high, long long &comparisons, long long &moves) {
    int mid = low + (high - low) / 2;
    swap(a[mid], a[high]);
    moves += 3;

    int pivot = a[high];
    moves++;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
            moves += 3;
        }
    }
    swap(a[i + 1], a[high]);
    moves += 3;
    return i + 1;
}

void quickSortHelper(vector<int> &a, int low, int high, long long &comparisons, long long &moves) {
    if (low < high) {
        int pi = partition(a, low, high, comparisons, moves);
        quickSortHelper(a, low, pi - 1, comparisons, moves);
        quickSortHelper(a, pi + 1, high, comparisons, moves);
    }
}

void customQuickSort(vector<int> &a, long long &comparisons, long long &moves) {
    if (!a.empty()) {
        quickSortHelper(a, 0, a.size() - 1, comparisons, moves);
    }
}

bool descendingCompare(int x, int y) {
    return x > y;
}

int nextRandom(unsigned int &seed) {
    seed = seed * 1103515245u + 12345u;
    return (seed / 65536u) % 32768u;
}

int main() {
    vector<int> sample = {45, 12, 85, 32, 89, 39, 69, 44, 42, 1, 45};

    sort(sample.begin(), sample.end());
    cout << "STL sort on vector (ascending): ";
    for (size_t i = 0; i < sample.size(); i++) {
        cout << sample[i] << " ";
    }
    cout << endl;

    sort(sample.begin(), sample.end(), descendingCompare);
    cout << "STL sort on vector (descending): ";
    for (size_t i = 0; i < sample.size(); i++) {
        cout << sample[i] << " ";
    }
    cout << endl;

    int n;
    cout << "Enter size for empirical comparison: ";
    if (!(cin >> n) || n <= 0) {
        n = 50000;
        cout << n << endl;
    }

    vector<int> original(n);
    unsigned int seed = 12345;
    for (int i = 0; i < n; i++) {
        original[i] = nextRandom(seed);
    }

    vector<int> a = original;
    long long quickComp = 0;
    long long quickMoves = 0;
    customQuickSort(a, quickComp, quickMoves);
    cout << "Custom Quick Sort -> Comparisons: " << quickComp << ", Moves: " << quickMoves << ", Total: " << (quickComp + quickMoves) << endl;

    vector<int> b = original;
    sort(b.begin(), b.end());
    cout << "STL sort sorted " << b.size() << " elements successfully." << endl;

    cout << endl;
    cout << "Comparison Summary:" << endl;
    cout << "Algorithm: STL sort uses Introsort (Quick Sort with median-of-three, Heap Sort fallback, Insertion Sort for small partitions)." << endl;
    cout << "Complexity: Guaranteed O(N log N) worst-case time complexity, O(log N) auxiliary space." << endl;
    cout << "Flexibility: Supports any RandomAccessIterator and custom predicate or comparator function." << endl;

    return 0;
}
