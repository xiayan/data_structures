#ifndef YANXIA_LAB10_LEFTISTHEAP_H_
#define YANXIA_LAB10_LEFTISTHEAP_H_

#include "SkewHeap.h"

// subclass SkewHeap.  Redefine merge and define computeRank

class LeftistHeap : public SkewHeap {
 private:
    int computeRank(TNode* h);    
    virtual TNode * merge(TNode* h1, TNode* h2);
};

#endif  /* YANXIA_LAB10_LEFTISTHEAP_H_ */
