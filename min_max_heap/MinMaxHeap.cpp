#include "MinMaxHeap.h"

MinMaxHeap::MinMaxHeap(ifstream &is) : size(0) {
    // build heap from file stream
    array = new int[DEFAULT_CAPACITY];
    int v;

    if (is.is_open()) {
        while (is >> v)
            array[++size] = v;
    }

#ifdef DEBUG
    debugHeap(1);
#else
    buildHeap();
#endif
}

MinMaxHeap::MinMaxHeap(int *data, int n) : size(n) {
    // build heap from another array
    array = new int[DEFAULT_CAPACITY];
    for (int i = 0; i < n; i++)
        array[i + 1] = data[i];

#ifdef DEBUG
    debugHeap(1);
#else
    buildHeap();
#endif
}

MinMaxHeap::~MinMaxHeap() {
    delete[] array;
}


bool MinMaxHeap::isEmpty() {
    return size == 0;
}

bool MinMaxHeap::isFull() {
    return size == DEFAULT_CAPACITY - 1;
}

void MinMaxHeap::levelOrder() {
    cout << "Level Order Traversal:\n";
    if (isEmpty()) {
        cout << "Empty Heap!\n";
        return;
    }
    // print the array level by level
    bool level = false;
    for (int i = 1; i <= size; i++) {
        if (atMinLevel(i) != level) {
            cout << endl;
            level = atMinLevel(i);
            if (level) cout << "Min Level: ";
            else       cout << "Max Level: ";
        }
        cout << array[i] << " ";
    }

    cout << endl << endl;
}

bool MinMaxHeap::atMinLevel(int i) {
    if (i < 1) {
        cout << "wrong index at atMinLevel\n";
        exit(1);
    }
    int level = log2(i);
    return (level % 2 == 0);
}


int MinMaxHeap::getParent(int child) {
    return (child / 2 >= 1) ? child / 2 : -1;
}

int MinMaxHeap::getGrandParent(int child) {
    return (child / 4 >= 1) ? child / 4 : -1;
}

int MinMaxHeap::getFirstGrandChild(int parent) {
    int gc = parent * 4;
    if (gc > size) return -1;
    else           return gc;
}

bool MinMaxHeap::hasLeftChild(int parent) {
    return (parent * 2 <= size);
}

bool MinMaxHeap::hasRightChild(int parent) {
    return (parent * 2 + 1 <= size);
}

bool MinMaxHeap::isGrandChild(int child, int parent) {
    return (child <= size) && (child >= 4 * parent && child <= 4 * parent + 3);
}

int MinMaxHeap::findMaxChild(int idx) {
    // find the max child from the subtree rooted at idx
    if (isLeaf(idx)) return -1;
    int gc = getFirstGrandChild(idx);
    int lID = 2 * idx;  // left child of idx
    int rID = 2 * idx + 1; // right child of idx
    int maxID;  // the idx of child with max value

    if (atMinLevel(idx) || gc < 0) {
        // if idx is at min level or it has no grandchild
        // the max id is either its left or right child
        if (!hasRightChild(idx)) maxID = lID;
        else maxID = (array[lID] >= array[rID]) ? lID : rID;
    } else {
        // if idx has grandchild or it is at max level
        // the max id can be one of the 4 grandchildren
        maxID = gc;
        int maxVal = array[maxID];
        for (int i = gc + 1; i <= gc + 3 && i <= size; i++) {
            if (array[i] > maxVal) {
                maxVal = array[i];
                maxID  = i;
            }
        }

        /* still need to compare maxID with idx's right child
         * for the case:
         * 
         *        20     max level
         *       /  \
         *     10   18   min level
         *    /  \
         *  11   12      max level
         *
         */
        maxID = (maxVal >= array[rID]) ? maxID : rID;
    }

    return maxID;
}

int MinMaxHeap::findMinChild(int idx) {
    // follows the same logic of findMaxChild
    if (isLeaf(idx)) return -1;
    int gc = getFirstGrandChild(idx);
    int lID = 2 * idx;
    int rID = 2 * idx + 1;
    int minID;

    if (!atMinLevel(idx) || gc < 0) {
        if (!hasRightChild(idx)) minID = lID;
        else minID = (array[lID] <= array[rID]) ? lID : rID;
    } else {
        minID = gc;
        int minVal = array[minID];
        for (int i = gc + 1; i <= gc + 3 && i <= size; i++) {
            if (array[i] < minVal) {
                minVal = array[i];
                minID  = i;
            }
        }

        /* still need to compare minID with idx's right child
         * for the case:
         * 
         *        3     min level
         *       / \
         *     10   4   max level
         *    /  \
         *   8    9     min level
         *
         */
        minID = (minVal <= array[rID]) ? minID : rID;
    }

    return minID;
}

bool MinMaxHeap::isLeaf(int idx) {
    return (idx > size / 2);
}

void MinMaxHeap::swimMin() {
    // swim up for only min levels
    int i = size;
    bool minLevel = atMinLevel(i);
    int gc = i;  // grandchild
    int gp;      // grandparent
    int val = array[i];

    // get the up min level
    if (minLevel)
        gp = getGrandParent(i);
    else
        gp = getParent(i);

    // in situ permutation
    while (gp > 0) {
        if (array[gp] > val) {
            array[gc] = array[gp];
            gc = gp;
            gp = getGrandParent(gp);
        } else {
            break;
        }
    }

    array[gc] = val;
}

void MinMaxHeap::swimMax() {
    // follows the same logic as swimMin
    int i = size;
    bool maxLevel = !atMinLevel(i);
    int gc = i;
    int gp;
    int val = array[i];

    if (maxLevel)
        gp = getGrandParent(i);
    else
        gp = getParent(i);

    while (gp > 0) {
        if (array[gp] < val) {
            array[gc] = array[gp];
            gc = gp;
            gp = getGrandParent(gp);
        } else {
            break;
        }
    }

    array[gc] = val;
}

void MinMaxHeap::insert(int item) {
    // if size overflow, exit
    if (size + 1 > DEFAULT_CAPACITY) exit(2);

    // add the new item and increase the size
    array[++size] = item;

    // get the parent index
    int parent = getParent(size);
    if (item == array[parent] || parent < 0) {
        return;
    } else if (item < array[parent]) {
#ifdef DEBUG
        debugHeap(2);
#else
        swimMin();
#endif
    } else {
#ifdef DEBUG
        debugHeap(3);
#else
        swimMax();
#endif
    }
}

int MinMaxHeap::findMin() {
    // if empty, return -1
    if (isEmpty()) return -1;

    // else, the min element is the root of MinMax heap
    return array[1];
}

int MinMaxHeap::findMax() {
    // if empty or has no max level entry, return -1
    if (size <= 1) return -1;

    // else, return the max child
    return array[findMaxChild(1)];
}

void MinMaxHeap::deleteMin() {
    // if heap is empty, error
    if (size == 0){
        cout << "DeleteMin for empty heap\n";
        exit(2);
    }

    // if heap size is 1, just decrease the size to 0 and return
    if (size == 1) {
        size--;
        return;
    }

    // replace the root of heap with the last element
    // and percolateDown
    array[1] = array[size--];

#ifdef DEBUG
    debugHeap(4, 1);
#else
    percolateDownMin(1);
#endif
}

void MinMaxHeap::deleteMax() {
    if (size == 0) {
        cout << "DeleteMax for empty heap\n";
        exit(2);
    }
    if (size == 1 || size == 2) {
        size--;
        return;
    }

    int max = findMaxChild(1);
    // replace max with the last element of the heap
    // and then percolateDown
    array[max] = array[size--];

#ifdef DEBUG
    debugHeap(5, max);
#else
    percolateDownMax(max);
#endif
}

void MinMaxHeap::buildHeap() {
    for (int i = size / 2; i > 0; i--)
        percolateDown(i);
}

void MinMaxHeap::percolateDown(int i) {
    if (atMinLevel(i))
        percolateDownMin(i);
    else
        percolateDownMax(i);
}

void MinMaxHeap::percolateDownMin(int idx) {
    // id is the final spot for the number at idx
    // sID is the index of smallest descendants.
    // pID is the index of the parent of sID
    int id  = idx;
    int sID = findMinChild(idx);
    int pID = getParent(sID);

    int s, p;
    int x = array[idx];

    // in situ permutation to find the right spot for number at idx
    while (sID > 0) {
        s = array[sID];
        p = array[pID];

        if (isGrandChild(sID, id)) {
            // if sID is a grand child of id
            if (x <= s) break;

            if (x > s)
                array[id] = s;
            if (x > p) {
                array[pID] = x;
                x = p;
            }

            id  = sID;
            sID = findMinChild(sID);
            pID = getParent(sID);
        } else {
            // if sID is a child of id
            if (x > s) {
                array[id] = s;
                id = sID;
            }
            break;
        }
    }

    array[id] = x;
}

void MinMaxHeap::percolateDownMax(int idx) {
    // follows the same logic of percolateDownMin
    int id  = idx;
    int sID = findMaxChild(idx);
    int pID = getParent(sID);
    // s is the value of max child, x is the value of idx
    int s, p;
    int x = array[idx];

    while (sID > 0) {
        s = array[sID];
        p = array[pID];

        if (isGrandChild(sID, id)) {
            if (x >= s) break;

            if (x < s)
                array[id] = s;
            if (x < p) {
                array[pID] = x;
                x = p;
            }

            id  = sID;
            sID = findMaxChild(sID);
            pID = getParent(sID);
        } else {
            if (x < s) {
                array[id] = s;
                id = sID;
            }
            break;
        }
    }

    array[id] = x;
}

// Debugging functions
// run "make test" to build the test module
// run "./test.out" to do the test

#ifdef DEBUG
unsigned long MinMaxHeap::heapSum() {
    // calculate the sum of all entries in the heap
    // this sum should be the same before and after
    // methods like swimMin, swimMax, percolateDown
    unsigned long s = 0;
    for (int i = 1; i <= size; i++)
        s += array[i];
    return s;
}

bool MinMaxHeap::check() {
    // simple and inefficient way to check if the current
    // array is a valid MinMaxHeap
    for (int i = 1; i <= size; i++) {
        bool level = atMinLevel(i);
        int lchild = (2 * i <= size) ? 2 * i : -1;
        int rchild = (2 * i + 1 <= size) ? 2 * i + 1 : -1;
        int gChil1 = (4 * i <= size) ? 4 * i : -1;
        int gChil2 = (4 * i + 1 <= size) ? 4 * i + 1 : -1;
        int gChil3 = (4 * i + 2 <= size) ? 4 * i + 2 : -1;
        int gChil4 = (4 * i + 3 <= size) ? 4 * i + 3 : -1;

        if (level) {
            if (lchild > 0 && array[i] > array[lchild]) return false;
            if (rchild > 0 && array[i] > array[rchild]) return false;
            if (gChil1 > 0 && array[i] > array[gChil1]) return false;
            if (gChil2 > 0 && array[i] > array[gChil2]) return false;
            if (gChil3 > 0 && array[i] > array[gChil3]) return false;
            if (gChil4 > 0 && array[i] > array[gChil4]) return false;
        } else {
            if (lchild > 0 && array[i] < array[lchild]) return false;
            if (rchild > 0 && array[i] < array[rchild]) return false;
            if (gChil1 > 0 && array[i] < array[gChil1]) return false;
            if (gChil2 > 0 && array[i] < array[gChil2]) return false;
            if (gChil3 > 0 && array[i] < array[gChil3]) return false;
            if (gChil4 > 0 && array[i] < array[gChil4]) return false;
        }
    }

    return true;
}

void MinMaxHeap::debugHeap(int c, int a) {
    // test method. c is the choice of method, a is the argument
    // heap sum should be the same before and after these methods
    // MinMax heap property should also be preserved
    string method;
    unsigned long before = heapSum();

    if (c == 1)      {
        buildHeap();
        method = "buildHeap";
    } else if (c == 2) {
        swimMin();
        method = "swimMin";
    } else if (c == 3) {
        swimMax();
        method = "swimMax";
    } else if (c == 4) {
        percolateDownMin(a);
        method = "deleteMin";
    } else if (c == 5) {
        percolateDownMax(a);
        method = "deleteMax";
    } else {
        cout << "choice should be between 1 to 5,\n";
        return;
    }

    bool valid = check();
    unsigned long after = heapSum();

    if (!valid || before != after) {
        cout << "\nError in " << method << endl;
        exit(1);
    }
}
#endif
