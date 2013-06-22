#include "BinaryHeap.h"

BinaryHeap::BinaryHeap(int capacity) : N(0), cap(capacity) {
    pq = new int[capacity + 1];
}

BinaryHeap::BinaryHeap(ifstream &is, int capacity) : N(0), cap(capacity) {
    // build heap from file stream
    pq = new int[capacity + 1];

    int v;
    if (is.is_open()) {
        while (is >> v)
            pq[++N] = v;
    }
    
    buildHeap();
}

BinaryHeap::BinaryHeap(int *array, int s) : N(s), cap(1.1 * s) {
    // build heap from array.  This constructor is specifically for
    // the timing test.  The capacity is slightly larger than
    // the size of the array.  This is to prevent heap overflow in
    // the insert/deleteMin timing test.

    pq = new int[cap + 1];

    for (int i = 0; i < s; i++)
        pq[i + 1] = array[i];

    buildHeap();
}

BinaryHeap::~BinaryHeap() {
    delete[] pq;
}

bool BinaryHeap::isEmpty() {
    return N == 0;
}

int BinaryHeap::getSize() {
    return N;
}

int BinaryHeap::findMin() {
    if (isEmpty()) {
        cout << "Heap underflow.\n";
        exit(1);
    }
    return pq[1];
}

void BinaryHeap::insert(int x) {
    if (N > cap) {
        cout << "Heap overflow.\n";
        exit(1);
    }
    
    // put the new item to the last position
    // increase the size and percolate up.
    pq[++N] = x;
    swim(N);
}

int BinaryHeap::deleteMin() {
    if (isEmpty()) {
        cout << "Heap underflow.\n";
        exit(1);
    }
    
    // exchange the first item with the last one
    // decrease the size and percolate down.
    exch(1, N);
    int min = pq[N--];
    sink(1);

    return min;
}

int BinaryHeap::deleteMax() {
    if (isEmpty()) {
        cout << "Heap underflow.\n";
        exit(1);
    }

    int maxID  = N / 2 + 1;
    int maxVal = pq[maxID];
    for (int i = maxID + 1; i <= N; i++) {
        if (pq[i] > maxVal) {
            maxID  = i;
            maxVal = pq[i];
        }
    }
    
    if (maxID == N) {
        N--;
    } else {
        pq[maxID] = pq[N--];
        swim(maxID);
    }

    return maxVal;
}

void BinaryHeap::swim(int k) {
    // in-situ permutation implementation of percolate up.
    int a = pq[k];
    while (k > 1 && pq[k / 2] > a) {
        pq[k] = pq[k / 2];
        k = k / 2;
    }

    pq[k] = a;
}

void BinaryHeap::buildHeap() {
    // for each internal node, percolate down
    for (int i = N / 2; i >= 1; i--)
        sink(i);
}

void BinaryHeap::sink(int k) {
    // in-situ permutation implementation of percolate down.
    int a = pq[k];
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && pq[j] > pq[j + 1]) j++;
        if (a <= pq[j]) break;
        
        pq[k] = pq[j];
        k = j;
    }

    pq[k] = a;
}

void BinaryHeap::exch(int i, int j) {
    int temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;
}

void BinaryHeap::print() {
    cout << "Level Order Traversal:\n";
    if (isEmpty()) {
        cout << "Empty Heap.\n";
        return;
    }

    int level = log2(1);
    for (int i = 1; i <= N; i++) {
        int currentLevel = log2(i);
        if (currentLevel != level) {
            level = currentLevel;
            cout << endl;
        }

        cout << pq[i] << " ";
    }

    cout << endl << endl;
}
