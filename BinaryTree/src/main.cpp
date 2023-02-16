#include <iostream>

#include "BinaryTree.h"

int main()
{
	BinaryTree<int> bst;

	// First Try
	//bst.insert(5);
	//bst.insert(2);
	//bst.insert(4);
	//bst.insert(9);

	// Second Try
	bst.insert(70);
	bst.insert(72);
	bst.insert(65);
	bst.insert(30);
	bst.insert(66);
	bst.insert(20);
	bst.insert(10);
	bst.insert(25);
	bst.insert(5);
	bst.insert(15);
	bst.insert(22);
	bst.insert(26);
	bst.insert(50);
	bst.insert(40);
	bst.insert(45);
	bst.insert(35);
	bst.insert(55);
	bst.insert(54);
	bst.insert(64);
	bst.insert(61);
	bst.insert(62);
	bst.insert(60);

	BinaryTree<int>::Iterator toDel = bst.find(65);

	bst.print();
	bst.erase(toDel);
	bst.print();

	return 0;
}