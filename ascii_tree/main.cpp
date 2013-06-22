#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "BinarySearchTree.h"
#include "AsciiTree.h"

void randomBST(BinarySearchTree &, int, int);

int main(int argc, const char *argv[]) {
	//Build tree using insert
    BinarySearchTree tree;
	int v;

	ifstream dataFile("data.txt");
	if(dataFile.is_open())
		while(dataFile >> v)
		tree.insert(v);			
	dataFile.close();
    
    cout << "SAMPLE TEST\n";
    cout << "---------------------------------\n";

    cout << "Original Tree\n";
    tree.preOrder();
    AsciiTree ascii;
    ascii.buildTree(tree);
    ascii.draw();
    
	// Test traversals
    cout << "Delete Min, Max, Root\n";
    tree.deleteMin();
    tree.deleteMax();
    tree.remove(7);
    tree.preOrder();
    ascii.buildTree(tree);
    ascii.draw();

    cout << "Insert 2, 17, 11, 16, 18\n";
    tree.insert(2);
    tree.insert(17);
    tree.insert(11);
    tree.insert(16);
    tree.insert(18);
    tree.preOrder();
    ascii.buildTree(tree);
    ascii.draw();
	
    cout << "Delete 6, 10, 13\n";
    tree.remove(6);
    tree.remove(10);
    tree.remove(13);
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();
    cout << "---------------------------------\n";

    cout << "\nMORE TESTS\n";
    cout << "---------------------------------\n";
    tree.clear();
    cout << "Test on empty tree\n";
    tree.deleteMin();
    tree.deleteMax();
    tree.remove(3);
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();

    cout << "\nTest on one node tree\n";
    tree.insert(3);
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();
    cout << "After deleteMin\n";
    tree.deleteMin();
    tree.preOrder();
    tree.inOrder();
    tree.insert(3);
    cout << "After deleteMax\n";
    tree.deleteMax();
    tree.preOrder();

    cout << "\nBuild a random binary search tree. 15 inserts(value between 1 - 30)\n";
    tree.clear();
    randomBST(tree, 15, 30); 
    ascii.buildTree(tree);
    ascii.draw();
    cout << "After deleting Min, Max\n";
    tree.deleteMin();
    tree.deleteMax();
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();
    
    cout << "After removing nodes with no child(4, 17)\n";
    tree.remove(4);
    tree.remove(17);
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();

    cout << "After removing nodes with 1 child(16, 26)\n";
    tree.remove(16);
    tree.remove(26);
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();

    cout << "After removing nodes with 2 children(7, 19)\n";
    tree.remove(7);
    tree.remove(19);
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();

    cout << "After removing root(11)\n";
    tree.remove(11);
    tree.preOrder();
    tree.inOrder();
    ascii.buildTree(tree);
    ascii.draw();

	return 0;
}

void randomBST(BinarySearchTree &bst, int nodes, int max) {
    srand(3);
    for (int i = 0; i < nodes; i++) {
        int number = rand() % max + 1;
        bst.insert(number);
    }    
}
