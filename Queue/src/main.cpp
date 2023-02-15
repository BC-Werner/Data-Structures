#include <iostream>
#include "Queue.hpp"

template<typename T>
void print(Queue<T>& queue, std::string name)
{
	Queue<T> temp;

	std::cout << "Printing " << name << "..." << std::endl;
	if (queue.empty()) 
	{
		std::cout << "EMPTY" << std::endl;
		return;
	}

	while (!queue.empty())
	{
		T val = queue.top();
		queue.pop();
		std::cout << val << " " << (queue.empty() ? "" : "-> ");
		temp.push(val);
	}
	std::cout << std::endl;

	queue.swap(temp);
}

int main()
{
	Queue<int> q1{ 1, 2, 3, 4, 5 };
	Queue<int> qCopy = q1;

	print(q1, "Q1");
	print(qCopy, "Q Copy");

	std::cout << "Moving Q Copy..." << std::endl;
	Queue<int> qMove = std::move(qCopy);

	print(qMove, "Q Move");
	print(qCopy, "Q Copy");

	return 0;
}