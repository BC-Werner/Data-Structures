#include <iostream>

#include "Vector.hpp"

int main()
{
	Vector<int> vec{ 1, 2, 3 };
	std::cout << "Initialize   Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;

	vec.push_back(55);
	std::cout << "Pushing...   Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;
	vec.push_back(30);
	std::cout << "Pushing...   Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;
	vec.push_back(6);
	std::cout << "Pushing...   Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;

	vec.pop_back();
	std::cout << "Popping...   Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;
	vec.shrink_to_fit();
	std::cout << "Shrinking... Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;

	std::cout << "Vector { ";
	for (size_t i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
	std::cout << "}" << std::endl;

	vec.clear();
	std::cout << "Clearing...  Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;

	std::cout << "Vector { ";
	for (size_t i = 0; i < vec.size(); i++) std::cout << vec[i] << " ";
	std::cout << "}" << std::endl;

	return 0;
}