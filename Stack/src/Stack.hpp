#pragma once
#include "../../LinkedList/src/List.hpp"

template <typename T, class Container = List<T>>
class Stack
{
public:
	Stack() : count(0) {}
	Stack(Stack<T, Container>&& other)
	{
		container = std::move(other.container);
		count = other.count;
	}
	~Stack() { clear(); }

	const bool empty() const { return count == 0; }
	const size_t Size() const { return count; }

	T& top() { return container.front(); }
	void push(T data) { container.push_front(data); count++; }
	void pop() { container.pop_front(); count--; }

	void swap(Stack<T, Container>& other) 
	{
		Stack<T, Container> tmp1;
		Stack<T, Container> tmp2;

		while (!other.empty())
		{
			tmp1.push(other.top());
			other.pop();
		}

		while (!empty())
		{
			tmp2.push(top());
			pop();
		}

		while (!tmp1.empty())
		{
			push(tmp1.top());
			tmp1.pop();
		}

		while (!tmp2.empty())
		{
			other.push(tmp2.top());
			tmp2.pop();
		}
	}

	void clear() { container.clear(); count = 0; }

private:
	size_t count;
	Container container;
};
