#include <iostream>

#include "BinaryTree.h"

int main()
{
	BinaryTree<int> bst{ 70, 72, 65, 30, 66, 20, 10, 25, 5, 15, 22, 26, 50, 40, 45, 35, 55, 54, 64, 61, 62, 60 };

	BinaryTree<int>::Iterator toDel = bst.find(50);

	std::cout << "BST: { ";
	bst.print();
	std::cout << " } size: " << bst.size() << std::endl;

	bst.erase(toDel);

	std::cout << "BST: { ";
	bst.print();
	std::cout << " } size: " << bst.size() << std::endl;


	BinaryTree<int>::Iterator iter = bst.begin();

	while (iter != bst.end())
	{
		std::cout << "Iter: " << *iter << std::endl;
		iter++;
	}

	std::cout << "BST: { ";
	for (auto it : bst)
	{
		std::cout << it << " ";
	}
	std::cout << " } size: " << bst.size() << std::endl;

	return 0;
}