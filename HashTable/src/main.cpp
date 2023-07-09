#include <iostream>

#include "HashTable.hpp"

int main()
{
	HashTable<int, int> ht;

	ht.insert(3, 0);
	ht.insert(2, 1);
	ht.insert(9, 2);
	ht.insert(8, 3);

	ht._print();

	return EXIT_SUCCESS;
}