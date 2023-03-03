#include <iostream>

#include "BinaryTree.h"

template <typename T>
void print(BinaryTree<T>& bst, std::string name)
{
	std::cout << name << ": { ";
	for (auto it : bst)
	{
		std::cout << it << " ";
	}
	std::cout << "} size: " << bst.size() << std::endl;
}

template <typename T>
void print_reverse(BinaryTree<T>& bst, std::string name)
{
	std::cout << name << " Reverse: { ";
	BinaryTree<int>::Iterator it = bst.find(72);
	while (it != bst.end())
	{
		std::cout << *it << " ";
		it--;
	}
	std::cout << "} size: " << bst.size() << std::endl;
}

int main()
{
	BinaryTree<int> bst{ 70, 72, 65, 30, 66, 20, 10, 25, 5, 15, 22, 26, 50, 40, 45, 35, 55, 54, 64, 61, 62, 60 };
	BinaryTree<int> bstCopy(bst);

	print_reverse(bst, "BST");

	BinaryTree<int>::Iterator toDelete = bst.find(50);
	print(bst, "BST");
	print(bstCopy, "BST Copy");

	bst.erase(toDelete);
	BinaryTree<int> bstMove(std::move(bst));
	print(bstMove, "BST Move");


	print(bst, "BST");
	print(bstCopy, "BST Copy");


	return 0;
}