#include <iostream>

#include "Vector.hpp"

template <typename T>
void print(Vector<T>& vec)
{
	std::cout << "Vector { ";
	for (auto val : vec) std::cout << val << " ";
	std::cout << "}" << std::endl;
}

int main()
{
	Vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::cout << "Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;
	print(vec);

	Vector<int> vecMove(std::move(vec));
	Vector<int> vecCopy(vecMove);

	std::cout << "Size/Capacity [" << vec.size() << "|" << vec.capacity() << "]" << std::endl;
	std::cout << "Size/Capacity [" << vecMove.size() << "|" << vecMove.capacity() << "]" << std::endl;
	std::cout << "Size/Capacity [" << vecCopy.size() << "|" << vecCopy.capacity() << "]" << std::endl;

	print(vec);
	print(vecMove);
	print(vecCopy);

	std::cout << "Front: " << vecMove.front() << " Back: " << vecMove.back() << std::endl;

	return 0;
}