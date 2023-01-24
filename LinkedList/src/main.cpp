#include <iostream>
#include <string>
#include "List.hpp"

template<typename T>
void print(List<T> & list, std::string name)
{
	std::cout << "\n" << name << "..." << std::endl;
	for (const auto& value : list) std::cout << value << " ";
	if (!list.empty()) std::cout << std::endl;
	std::cout << "Size: " << list.size() << std::endl;
}

int main()
{
	std::cout << "\n ================================= Instantiation with Initializer List ================================== " << std::endl;
	std::cout << "List of Integers" << std::endl;
	List<int> intList{ 4, 6, 2, 1, 44, 1000, 39, 343, 33, 144};

	print(intList, "intList");

	std::cout << "\n ================================= Copy Constructor ================================== " << std::endl;
	List<int> copyList(intList);
	print(copyList, "Copy List");

	std::cout << "\n ================================= Move Constructor ================================== " << std::endl;
	List<int> l1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	print(l1, "L1");

	List<int> l2(std::move(l1));
	print(l2, "L2");
	print(l1, "L1");

	std::cout << "\n =========================== Pushing and Popping =========================== " << std::endl;
	std::cout << "Pushing front..." << std::endl;
	intList.push_front(3);
	std::cout << "Pushing back..." << std::endl;
	intList.push_back(9);

	print(intList, "intList");

	std::cout << "\nPopping front..." << std::endl;
	intList.pop_front();
	std::cout << "Popping back..." << std::endl;
	intList.pop_back();

	print(intList, "intList");

	std::cout << "\n =========================== Insertion ===================================== " << std::endl;
	std::cout << "Inserting at first position..." << std::endl;
	intList.insert(intList.begin(), 0);

	print(intList, "intList");

	int target = 1000;
	std::cout << "\nInserting before node with value of " << target << "..." << std::endl;
	List<int>::Iterator it = intList.begin();
	while (it != intList.end() && *it != target)
		it++;
	intList.insert(it, target - 1);

	print(intList, "intList");

	std::cout << "\n =========================== Reversing ===================================== " << std::endl;
	std::cout << "Reversing..." << std::endl;
	intList.reverse();

	print(intList, "intList");

	std::cout << "\n =========================== Sorting ======================================= " << std::endl;
	std::cout << "Sorting..." << std::endl;
	intList.sort();

	print(intList, "intList");

	std::cout << "\nSorting Reverse..." << std::endl;
	intList.sort(std::greater<int>());

	print(intList, "intList");

	std::cout << "\n =========================== Erasing ======================================= " << std::endl;
	std::cout << "Removing odd numbers..." << std::endl;
	List<int>::Iterator startIt = intList.begin();
	while (startIt != intList.end())
	{
		if (*startIt % 2 != 0) startIt = intList.erase(startIt);
		else startIt++;
	}

	print(intList, "intList");

	std::cout << "\n =========================== Clearing ====================================== " << std::endl;
	std::cout << "Clearing..." << std::endl;
	intList.clear();

	print(intList, "intList");

	return 0;
}