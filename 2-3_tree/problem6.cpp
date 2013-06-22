#include <stdlib.h>
#include <fstream>
#include "./TwoThreeTree.h"
#include "./AsciiTree.h"

int main(int argc, const char *argv[]) {
    // Build tree using insert
    TwoThreeTree tree;
    AsciiTree ascii;
    
    tree.insert(5);
    tree.insert(12);
    tree.insert(15);
    tree.insert(8);
    tree.insert(9);
    tree.insert(4);
    tree.insert(1);
    tree.insert(18);
    tree.insert(6);
    tree.insert(16);
    tree.insert(11);
    tree.insert(2);
    tree.insert(16);
    tree.insert(7);
    tree.insert(8);
    tree.remove(1);
    tree.remove(9);
    tree.remove(18);

    ascii.buildTree(tree);
    ascii.draw();

    return 0;
}
