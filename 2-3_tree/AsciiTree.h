/* 
 * Helper class to debug the TwoThreeTree code.  Objects from this class takes a TwoThreeTree
 * as argument and print out the structure of BST on console.
 * 
 * Again, this class is for pure debugging purpose.  Please do not include it in grading.
*/

#ifndef YANXIA_LAB8_ASCIITREE_H_
#define YANXIA_LAB8_ASCIITREE_H_
#include <string>
#include <vector>
#include "TwoThreeTree.h"

using std::cout;
using std::endl;
using std::vector;

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
        int side;
        bool isLeaf;
        bool twoNode;
        AsciiNode *left;
        AsciiNode *middle;
        AsciiNode *right;
        AsciiNode *parent;
        AsciiNode() : value(""), order(0), level(0), edgeL(0), \
                      edgeR(0), x(0), left(NULL), right(NULL) { }
        void print() {
            cout << value << " ";
        }
    };

    AsciiNode *root;
    int ranking;
    int offset;

    AsciiNode * buildTree(TNode *t);
    void clear();
    void clear(AsciiNode *t);
    void inOrder() { inOrder(root); }
    void inOrder(AsciiNode *t);
    int  orderToLength(int x);
    void assignX() { inOrder(); assignX(root); }
    void assignX(AsciiNode *t);  // use pre order traversal to implement
    void getOffset();
    void drawLevel(const vector<AsciiNode *> &n);
    void drawEdges(const vector<AsciiNode *> &n);

 public:
    AsciiTree();
    ~AsciiTree() { clear(); }

    void buildTree(const TwoThreeTree &bst);
    void draw();
};

#endif  // YANXIA_LAB8_ASCIITREE_H_
