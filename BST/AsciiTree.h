/* 
 * Helper class to debug the BinarySearchTree code.  Objects from this class takes a BinarySearchTree 
 * as argument and print out the structure of BST on console.
 * 
 * Again, this class is for pure debugging purpose.  Please do not include it in grading.
 */


#ifndef ASCIITREE_H_
#define ASCIITREE_H_
#include <string>
#include <vector>
#include "BinarySearchTree.h"

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
        AsciiNode *left;
        AsciiNode *right;
        AsciiNode() : value(""), order(0), level(0), edgeL(0), edgeR(0), x(0), left(NULL), right(NULL) {}
    };
    
    AsciiNode *root;
    int ranking;
    int offset;
    
    AsciiNode * buildTree(TNode *);
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
    
    void buildTree(BinarySearchTree &bst);
    void draw();
};

#endif /* ASCIITREE_H_ */
