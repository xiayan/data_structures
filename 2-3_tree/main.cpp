#include <stdlib.h>
#include <fstream>
#include "TwoThreeTree.h"
#include "AsciiTree.h"

int main(int argc, const char *argv[]) {
    // Build tree using insert
    TwoThreeTree tree;
    AsciiTree ascii;
    
    cout << "------------SAMPLE TEST------------\n\n";
    int v;
    std::ifstream dataFile("data.txt");
    if (dataFile.is_open())
        while (dataFile >> v)
            tree.insert(v);
    dataFile.close();
    
    cout << "ORIGINAL 2-3 TREE:\n";
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "DELETE MIN\n";
    tree.deleteMin();
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "REMOVE 28\n";
    tree.remove(28);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << endl;

    cout << "------------MORE TEST------------\n";
    tree.clear();
    cout << "BUILDING TREE\n";
    tree.insert(15);
    tree.insert(13);
    tree.insert(11);
    tree.insert(9);
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(2);
    tree.insert(23);
    tree.insert(25);
    tree.insert(27);
    tree.insert(33);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();
    
    cout << "INSERT INTO 2-NODE(INSERT 1, 10, 26)\n";
    tree.insert(1);
    tree.insert(10);
    tree.insert(26);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "INSERT INTO 3-NODE(INSERT 12)\n";
    tree.insert(12);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "REMOVE FROM 3-NODE(REMOVE 23)\n";
    tree.remove(23);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "REMOVE FROM 2-NODE(REMOVE 5)\n";
    tree.remove(5);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "REMOVE FROM 2-NODE(REMOVE 9)\n";
    tree.remove(9);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "REMOVE FROM 2-NODE(REMOVE 2)\n";
    tree.remove(2);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    cout << "REMOVE FROM 2-NODE(REMOVE 26)\n";
    tree.remove(26);
    ascii.buildTree(tree);
    ascii.draw();
    tree.levelOrder();

    return 0;
}
