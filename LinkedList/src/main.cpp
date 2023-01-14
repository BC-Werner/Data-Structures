#include <iostream>
#include "List.hpp"

int main()
{
	std::cout << "\n ================================= Instantiation with Initializer List ================================== " << std::endl;
	std::cout << "List of Integers" << std::endl;
	List<int> intList{ 4, 6, 2, 1, 44, 1000, 39, 343, 33, 144};

	std::cout << "\nPrinting..." << std::endl;
	for (const auto& val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\n =========================== Pushing and Popping =========================== " << std::endl;
	std::cout << "Pushing front..." << std::endl;
	intList.push_front(3);
	std::cout << "Pushing back..." << std::endl;
	intList.push_back(9);

	std::cout << "\nPrinting..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\nPopping front..." << std::endl;
	intList.pop_front();
	std::cout << "Popping back..." << std::endl;
	intList.pop_back();

	std::cout << "\nPrinting..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\n =========================== Insertion ===================================== " << std::endl;
	std::cout << "Inserting at first position..." << std::endl;
	intList.insert(intList.begin(), 0);

	std::cout << "Printing..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	int target = 1001;
	std::cout << "\nInserting before node with value of " << target << "..." << std::endl;
	List<int>::Iterator it = intList.begin();
	while (it != intList.end() && *it != target)
		it++;
	intList.insert(it, target - 1);

	std::cout << "Printing..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\n =========================== Reversing ===================================== " << std::endl;
	std::cout << "Reversing..." << std::endl;
	intList.reverse();

	std::cout << "Printing..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\n =========================== Sorting ======================================= " << std::endl;
	std::cout << "Sorting..." << std::endl;
	intList.sort();

	std::cout << "Printing..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\nSorting Reverse..." << std::endl;
	intList.sort(std::greater<int>());

	std::cout << "Printing..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\n =========================== Erasing ======================================= " << std::endl;
	std::cout << "Removing odd numbers..." << std::endl;
	List<int>::Iterator startIt = intList.begin();
	while (startIt != intList.end())
	{
		if (*startIt % 2 != 0) startIt = intList.erase(startIt);
		else startIt++;
	}

	std::cout << "Printing..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	std::cout << "\n =========================== Clearing ====================================== " << std::endl;
	std::cout << "Clearing..." << std::endl;
	intList.clear();

	std::cout << "\nPrinting..." << std::endl;
	for (auto val : intList) std::cout << val << std::endl;
	std::cout << "Size: " << intList.Size() << std::endl;

	return 0;
}