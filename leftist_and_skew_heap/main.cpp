#include "BinaryHeap.h"
#include "SkewHeap.h"
#include "LeftistHeap.h"
#include "Timer.h"
#include <stdlib.h>
#include <climits>
#include <ctime>

namespace Test {
    int S = 50000;  // start size
    int E = 400000; // end size
    int inc = 2;  // size increment
    int step = 4; // number of increments
    int reps = 5; // number of experiments
};

using namespace std;

void heapTests(int i, int s);

int main() {
    for (int i = 0; i < Test::reps; i++) {
        cout << "Seed: " << i << endl;
        int S = Test::S;
        for (int j = 0; j < Test::step; j++) {
            cout << "Size: " << S << endl;
            heapTests(i, S);

            S *= Test::inc;
        }
        cout << "-----------------------\n" << endl;
    }

    return 0;
}

void heapTests(int seed, int s) {
    srand(seed);  // seed the random number generator
    int array[s]; // create the array to hold random numbers
    int deletes = 0, inserts = 0;
    for (int i = 0; i < s; i++)
        array[i] = rand() % (4 * s) + 1; // number between 1 to 4n + 1

    Timer t;
    
    // binary heap building
    cout << "Binary Heap\n";
    t.start();
    BinaryHeap bHeap(array, s);
    cout << "Build time: ";
    t.printTime(t.stop());
    
    // binary heap insert/deleteMin
    srand(seed);
    t.start();
    for (int j = 0; j < s * 0.1; j++) {
        float r = (float)rand() / (float)RAND_MAX;
        if (r < 0.5) {
            bHeap.deleteMin();
            deletes++;
        } else {
            bHeap.insert(rand() % (4 * s) + 1);
            inserts++;
        }
    }
    cout << "Insert/Delete Time: ";
    t.printTime(t.stop());
    cout << inserts << " inserts\n";
    cout << deletes << " deletes\n\n";
    
    // leftist heap building
    inserts = 0;
    deletes = 0;
    cout << "LeftistHeap Heap\n";
    t.start();
    LeftistHeap lHeap;
    for (int i = 0; i < s; i++) {
        lHeap.insert(array[i]);
    }
        
    cout << "Build time: ";
    t.printTime(t.stop());
    
    // leftist heap insert/deleteMin
    srand(seed);
    t.start();
    for (int j = 0; j < s * 0.1; j++) {
        float r = (float)rand() / (float)RAND_MAX;
        if (r < 0.5) {
            lHeap.deleteMin();
            deletes++;
        } else {
            lHeap.insert(rand() % (4 * s) + 1);
            inserts++;
        }
    }
    cout << "Insert/Delete Time: ";
    t.printTime(t.stop());
    cout << inserts << " inserts\n";
    cout << deletes << " deletes\n\n";

    // skew heap building
    inserts = 0;
    deletes = 0;
    cout << "Skew Heap\n";
    t.start();
    SkewHeap sHeap;
    for (int i = 0; i < s; i++) {
        sHeap.insert(array[i]);
    }
    cout << "Build time: ";
    t.printTime(t.stop());
    
    // skew heap insert/delete
    srand(seed);
    t.start();
    for (int j = 0; j < s * 0.1; j++) {
        float r = (float)rand() / (float)RAND_MAX;
        if (r < 0.5) {
            sHeap.deleteMin();
            deletes++;
        } else {
            sHeap.insert(rand() % (4 * s) + 1);
            inserts++;
        }
    }

    cout << "Insert/Delete Time: ";
    t.printTime(t.stop());
    cout << inserts << " inserts\n";
    cout << deletes << " deletes\n\n";
}
