/* 
 * Helper class to debug the three types of heaps.  Objects from this class takes a any of the three heaps 
 * as argument and print out the structure of heap on console.
 * 
 * Again, this class is for pure debugging purpose.  Please do not include it in grading.
 */


#ifndef ASCIITREE_H_
#define ASCIITREE_H_
#include "SkewHeap.h"
#include "BinaryHeap.h"
#include <string>
#include <vector>

using namespace std;
class TNode;

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
    
    AsciiNode * buildTree(TNode *);
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
    
    void buildTree(SkewHeap &lh);
    void buildTree(BinaryHeap &heap);
    void draw();
};

#endif /* ASCIITREE_H_ */
