#include <iostream>
#include "Queue.hpp"

template<typename T>
void print(Queue<T>& queue, std::string name)
{
	Queue<T> temp;

	std::cout << name << "..." << std::endl;
	if (queue.empty()) 
	{
		std::cout << "EMPTY" << std::endl;
		return;
	}

	print(queue);
}

template<typename T>
void print(Queue<T>& queue)
{
	if (queue.empty()) return;

	T val = queue.top();
	queue.pop();
	std::cout << val << " " << (queue.empty() ? "" : "-> ");
	print(queue);
	queue.push(val);
}

int main()
{
	Queue<int> q1{ 1, 2, 3, 4, 5 };

	print(q1, "Q1");

	std::cout << "Popping..." << std::endl;
	while (!q1.empty())
		q1.pop();

	print(q1, "Q1");

	return 0;
}