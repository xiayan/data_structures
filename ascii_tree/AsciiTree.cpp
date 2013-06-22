/* 
 * Helper class to debug the BinarySearchTree code.  Objects from this class takes a BinarySearchTree 
 * as argument and print out the structure of BST on console.
 * 
 * Again, this class is for pure debugging purpose.  Please do not include it in grading.
 */

#include "AsciiTree.h"
#include <sstream>
#include <queue>

AsciiTree::AsciiTree() : root(NULL), ranking(0), offset(0) {

}

void AsciiTree::buildTree(BinarySearchTree &bst) {
    clear();
    root = buildTree(bst.root);
    if (root)
        root->level = 0;
}

AsciiTree::AsciiNode * AsciiTree::buildTree(TNode *t) {
    if (t == NULL) return NULL;

    AsciiNode *newNode = new AsciiNode();
    stringstream ss;
    ss << t->value;
    newNode->value = ss.str();

    newNode->left =  buildTree(t->left );
    newNode->right = buildTree(t->right);

    return newNode;
}

void AsciiTree::clear() {
    ranking = 0;
    clear(root);
    root = NULL;
}

void AsciiTree::clear(AsciiNode *t) {
    if (t == NULL) return;

    clear(t->left);
    clear(t->right);
    delete t;
}

void AsciiTree::inOrder(AsciiNode *t) {
    if (t == NULL) return;

    inOrder(t->left);
    t->order = ranking;
    ranking += (t->value.length() + 1);
    inOrder(t->right);
}

int  AsciiTree::orderToLength(int o) {
    return o;
}

void AsciiTree::assignX(AsciiNode *t) {
    if (t == NULL) return;

    int diffL, diffR;
    AsciiNode *left =  t->left;
    AsciiNode *right = t->right;

    if (left && right) {
        diffL = t->order - left->order;
        diffR = right->order - t->order;
        t->edgeL = orderToLength(diffL);
        t->edgeR = orderToLength(diffR);
        left->x  = t->x - t->edgeL;
        right->x = t->x + t->edgeR;
    } else if (left) {
        diffL = t->order - left->order;
        t->edgeL = orderToLength(diffL);
        t->edgeR = 0;
        left->x = t->x - t->edgeL;
    } else if (right) {
        diffR = right->order - t->order;
        t->edgeR = orderToLength(diffR);
        t->edgeL= 0;
        right->x = t->x + t->edgeR;
    } else {
        t->edgeL = 0;
        t->edgeR = 0;
    }
    
    //cout << t->value << "\t" << t->edgeLength << "\t" << t->x << endl;
    assignX(left);
    assignX(right);
}

void AsciiTree::getOffset() {
    if (root == NULL) return;

    AsciiNode *runner = root;
    while (runner->left)
        runner = runner->left;

    offset = -(runner->x);
}

void AsciiTree::draw() {
    if (root == NULL) return;

    assignX();
    getOffset();

    vector<AsciiNode *> levelNodes;
    queue<AsciiNode *> fifo;
    int nextLevel = root->level;

    fifo.push(root);
    while (!fifo.empty()) {
        while (!fifo.empty() && fifo.front()->level == nextLevel) {
            AsciiNode *current = fifo.front();
            levelNodes.push_back(current);
            if (current->left)  {
                current->left->level = current->level + 1;
                fifo.push(current->left);
            }
            if (current->right) {
                current->right->level = current->level + 1;
                fifo.push(current->right);
            }
            fifo.pop();
        }
        
        if (!fifo.empty())
            nextLevel = fifo.front()->level;
        
        drawLevel(levelNodes);
        drawEdges(levelNodes);
        levelNodes.clear();
    }
}

string multipleSpaces(int n) {
    string result = "";
    for (int i = 0; i < n; i++)
        result += " ";
    return result;
}

void AsciiTree::drawLevel(vector<AsciiNode *> &levelNodes) {
    string levelResult = multipleSpaces(levelNodes[0]->x + offset) + levelNodes[0]->value;

    AsciiNode *previous, *current;
    for (int i = 1; i < (int)levelNodes.size(); i++) {
        previous = levelNodes[i - 1];
        current = levelNodes[i];
        levelResult += (multipleSpaces(current->x - previous->x - previous->value.length()) + current->value);
    }

    cout << levelResult << endl;
}

void AsciiTree::drawEdges(vector<AsciiNode *> &levelNodes) {
    string levelResult = "";
    int lastX = 0;
    int centerL, centerR;
    AsciiNode *current, *left, *right;

    for (unsigned int i = 0; i < levelNodes.size(); i++) {
        current = levelNodes[i];
        left    = current->left;
        right   = current->right;
        centerL = current->edgeL / 2;
        centerR = current->edgeR / 2;

        if (left == NULL && right == NULL) continue;
        if (left) {
            int leftEdge = current->x + offset - centerL;
            levelResult += multipleSpaces(leftEdge - lastX) + "/";
            lastX = leftEdge + 1;
        }
        if (right) {
            int rightEdge = current->x + offset + current->value.length() + centerR;
            levelResult += multipleSpaces(rightEdge - lastX - 1) + "\\";
            lastX = rightEdge;
        }
    }
    cout << levelResult << endl;
}
