/* 
 * Helper class to debug the TwoThreeTree code.  Objects from this class takes a TwoThreeTree
 * as argument and print out the structure of BST on console.
 * 
 * Again, this class is for pure debugging purpose.  Please do not include it in grading.
*/

#include "AsciiTree.h"
#include <sstream>
#include <string>
#include <queue>
#include <vector>

using std::stringstream;
using std::queue;
using std::string;

AsciiTree::AsciiTree() : root(NULL), ranking(0), offset(0) { }

void AsciiTree::buildTree(const TwoThreeTree &bst) {
    // if (bst.root == NULL) return;
    clear();
    root = buildTree(bst.root);
    if (root)
        root->level = 0;
}

AsciiTree::AsciiNode * AsciiTree::buildTree(TNode *t) {
    if (t == NULL) return NULL;

    AsciiNode *newNode = new AsciiNode();
    stringstream ss;
    if (t->isLeaf) {
        ss << t->key;
    } else {
        if (t->rlow == -1)
            ss << "[" << t->mlow << ", " << "-]";
        else
            ss << "[" << t->mlow << ", " << t->rlow << "]";
    }

    newNode->value = ss.str();

    newNode->side = t->side;
    newNode->twoNode = false;
    if (t->rlow == -1)
        newNode->twoNode = true;

    newNode->isLeaf = t->isLeaf;

    newNode->left   = buildTree(t->left);
    if (newNode->left)
        newNode->left->parent = newNode;
    newNode->middle = buildTree(t->middle);
    if (newNode->middle)
        newNode->middle->parent = newNode;
    newNode->right  = buildTree(t->right);
    if (newNode->right)
        newNode->right->parent = newNode;

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
    clear(t->middle);
    clear(t->right);
    delete t;
}

void AsciiTree::inOrder(AsciiNode *t) {
    if (t == NULL) return;

    inOrder(t->left);
    inOrder(t->middle);
    inOrder(t->right);
    if (t->isLeaf && !t->parent->twoNode) {
        if (t->side == -1) {
            t->x = ranking;
            ranking = (t->x + t->value.length());
        } else if (t->side == 0) {
            t->x = ranking + t->parent->value.length()/2 - \
                   t->value.length() + 1;
            ranking = ranking + t->parent->value.length();
            if (t->parent->right == NULL) ranking += 3;
        } else {
            t->x = ranking;
            ranking = (t->x + t->value.length() + 3);
        }
    } else if (t->isLeaf && t->parent->twoNode) {
        if (t->side == -1) {
            t->x = ranking;
            ranking = (t->x + t->value.length());
        } else {
            t->x = ranking + t->parent->value.length();
            ranking = (t->x + t->value.length() + 3);
        }
    } else {
        if (!t->twoNode) {
            if (t->middle->isLeaf) {
                t->x = t->middle->x - t->value.length()/2 + \
                       t->middle->value.length() - 1;
            } else {
                int diff = t->value.length() - t->middle->value.length();
                t->x = t->middle->x - diff / 2;
            }

        } else {
            if (t->middle->isLeaf) {
                t->x = t->left->x + t->left->value.length();
            } else {
                int diff = (t->middle->x - t->left->x - \
                        t->left->value.length())/2;
                t->x = t->left->x + t->left->value.length() + \
                       diff - t->value.length() / 2;
            }
        }
    }
}

int  AsciiTree::orderToLength(int o) {
    return o;
}

void AsciiTree::assignX(AsciiNode *t) {
    if (t == NULL) return;

    int diffL, diffR;
    AsciiNode *left =  t->left;
    AsciiNode *middle = t->middle;
    AsciiNode *right = t->right;

    if (left && right) {
        diffL = t->order - left->order;
        diffR = right->order - t->order;
        t->edgeL = orderToLength(diffL);
        t->edgeR = orderToLength(diffR);
        left->x  = t->x - t->edgeL;
        right->x = t->x + t->edgeR;
        middle->x = t->x;
    } else if (left) {
        diffL = t->order - left->order;
        t->edgeL = orderToLength(diffL);
        t->edgeR = 0;
        left->x = t->x - t->edgeL;
        middle->x = t->x;
    } else {
        t->edgeL = 0;
        t->edgeR = 0;
    }

    // cout << t->value << "\t" << t->edgeLength << "\t" << t->x << endl;
    assignX(left);
    assignX(middle);
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
    if (root == NULL) {
        cout << "Empty Tree!\n\n";
        return;
    }

    if (root->isLeaf) {
        root->print();
        cout << endl << endl;
        return;
    }

    inOrder(root);
    // assignX();
    // getOffset();

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
            if (current->middle) {
                current->middle->level = current->level + 1;
                fifo.push(current->middle);
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
        // drawEdges(levelNodes);
        levelNodes.clear();
    }
    cout << endl;
}

string multipleSpaces(int n) {
    string result = "";
    for (int i = 0; i < n; i++)
        result += " ";
    return result;
}

void AsciiTree::drawLevel(const vector<AsciiNode *> &levelNodes) {
    string levelResult = multipleSpaces(levelNodes[0]->x + offset) + \
                         levelNodes[0]->value;

    AsciiNode *previous, *current;
    for (unsigned int i = 1; i < levelNodes.size(); i++) {
        previous = levelNodes[i - 1];
        current = levelNodes[i];
        levelResult += (multipleSpaces(current->x - \
                    previous->x - previous->value.length()) + current->value);
    }

    cout << levelResult << endl;
}

void AsciiTree::drawEdges(const vector<AsciiNode *> &levelNodes) {
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
            int rightEdge = current->x + offset + \
                            current->value.length() + centerR;
            levelResult += multipleSpaces(rightEdge - lastX - 1) + "\\";
            lastX = rightEdge;
        }
    }
    cout << levelResult << endl;
}
