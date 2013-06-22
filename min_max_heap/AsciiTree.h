/* 
 * Helper class to debug the MinMaxHeap code.  Objects from this class takes a MinMaxHeap
 * as argument and print out the structure of heap on console.
 * 
 * Again, this class is for pure debugging purpose.  Please do not include it in grading.
 */


#ifndef YANXIA_LAB9_ASCIITREE_H_
#define YANXIA_LAB9_ASCIITREE_H_
#include "MinMaxHeap.h"
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class AsciiTree {
private:
    struct AsciiNode {
        std::string value;
        int order;
        int level;
        int edgeL;
        int edgeR;
        int x;
        int index;
        AsciiNode *left;
        AsciiNode *right;
        AsciiNode() : value(""), order(0), level(0), edgeL(0), edgeR(0), x(0), left(NULL), right(NULL) {}
    };

    AsciiNode *root;
    int ranking;
    int offset;
    int xMax;

    AsciiNode * buildTree(int *array, int n, int i);
    void clear();
    void clear(AsciiNode *t);
    void inOrder() { inOrder(root); }
    void inOrder (AsciiNode *);
    int  orderToLength(int);
    void assignX() { inOrder(); assignX(root); }
    void assignX(AsciiNode *);  // use pre order traversal to implement
    void getOffset();
    void drawLevel(vector<AsciiNode *> &);
    void drawEdges(vector<AsciiNode *> &);

public:
    AsciiTree();
    ~AsciiTree() { clear(); }

    void buildTree(MinMaxHeap &heap);
    void draw();
};

#endif /* YANXIA_ASCIITREE_H_ */
