#include "bst.h"
#include <iostream>


int main(void){
	BST<int> tree;
	tree.insert(15);
	tree.insert(10);
	tree.insert(25);
	tree.insert(3);
	tree.insert(1);
	tree.insert(4);
	tree.insert(12);
	tree.insert(35);
	tree.insert(30);
	tree.insert(40);
	std::cout << "inorder: ";
	tree.printInorder();
	std::cout << "preorder: ";
	tree.printPreorder();
	std::cout << "postorder: ";
	tree.printPostorder();
	std::cout << "breadfirst: ";
	tree.printBreadthfirst();
}