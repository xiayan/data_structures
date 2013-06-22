#ifndef YANXIA_LAB11_BNODE_H_
#define YANXIA_LAB11_BNODE_H_

#include <iostream>
#include <sstream>

using namespace std;

class BNode {	
 public:
    int order;
    int key;
    BNode *l_sib;
    BNode *r_sib;
    BNode *f_child;

    // data fields for TQueue class (Level order traversal)
    BNode *next;
    int level;
    int x;
    string content;
    int len;
	
	BNode(int k = -1) : order(0), key(k), r_sib(NULL), \
                        f_child(NULL), next(NULL), \
                        level(0), x(0) {
        l_sib = this;

        stringstream ss;
        ss << key;
        content = ss.str();
        len = ss.str().length();
    }
};

#endif /* YANXIA_LAB11_BNODE_H_ */
