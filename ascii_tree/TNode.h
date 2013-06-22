#ifndef TNODE_H_
#define TNODE_H_

#include <iostream>
using namespace std;

class TNode
{
public:
    int value;
    TNode* left;
    TNode* right;
    
    TNode(int v, TNode* lt = NULL, TNode* rt = NULL) : value(v), left(lt), right(rt) { }
    
    void print(){
        cout << value << " ";
    }
};

#endif /* TNODE_H_ */
