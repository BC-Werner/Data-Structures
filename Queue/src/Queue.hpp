#pragma once
#include "../../LinkedList/src/List.hpp"
#include <initializer_list>

template <typename T, class Container = List<T>>
class Queue
{
public:
	Queue() : m_size(0) {}
	Queue(const Queue<T, Container>& other) : m_size(other.m_size), container(other.container) {}
	Queue(const std::initializer_list<T>& il) : m_size(il.size()), container(il) {}
	Queue(Queue<T, Container>&& other) : m_size(0), container() { other.swap(*this); }

	void swap(Queue<T, Container>& other)
	{
		std::swap(m_size, other.m_size);
		container.swap(other.container);
	}

private:
	size_t m_size;
	Container container;
};
