#pragma once

#include <initializer_list>
#include <iostream>

template<typename T>
class Vector
{
public:
	Vector()
	{
		allocate(1);
	}
	Vector(const std::initializer_list<T>& il)
	{
		allocate(il.size());

		auto iter = il.begin();
		for (size_t i = 0; i < il.size() && iter != il.end(); i++)
		{
			m_data[i] = *iter;
			iter++;
			m_size++;
		}
	}

	// Capacity
	bool empty() const { return m_size == 0; }
	size_t size() const { return m_size; }
	void reserve(size_t newCap) { if (newCap <= m_capacity) return; allocate(newCap); }
	size_t capacity() const { return m_capacity; }
	void shrink_to_fit() { if (m_size != m_capacity) allocate(m_size); }

	// Modifiers
	void clear() 
	{
		m_size = 0;
		allocate(m_capacity);
	};
	//void insert(Iterator pos, const T& data) {};
	//Iterator erase(Iterator pos) {};
	//Iterator erase(Iterator start, Iterator end) {};
	void push_back(const T& data) 
	{
		if (m_size >= m_capacity) allocate(m_capacity * 2);
		m_data[m_size] = data;
		m_size++;
	};
	void pop_back() { if (m_size > 0) resize(m_size - 1); };
	void resize(size_t count) 
	{
		if (count > m_capacity) allocate(count);
		if (m_size <= count)
		{
			for (size_t i = m_size; i < count; i++)
			{
				m_data[i] = T();
			}
			m_size = count;
			return;
		}

		if (m_size > count) m_size = count;

	}

	// Iterators

	// Element Access
	T& operator[](size_t index) { return m_data[index]; }
	const T& operator[](size_t index) const { return m_data[index]; }
	// Below throws std::out_of_range
	// if (pos >= m_size)
	//T& at(size_t pos) {}
	//const T& at(size_t pos) const {}

	T& front() { return m_data[0];					/* Should eventually return *begin(); */}
	const T& front() const { return m_data[0];		/* Should eventually return *begin(); */} 
	T& back() { return m_data[m_size-1];				/* Should eventually return *std::prev(end()); */ }
	const T& back() const { return m_data[m_size-1];	/* Should eventually return *std::prev(end()); */ }

private:
	void allocate(size_t newCap)
	{
		T* newBlock = new T[newCap];

		if (newCap < m_size)
			m_size = newCap;

		for (size_t i = 0; i < m_size; i++)
			newBlock[i] = m_data[i];

		delete[] m_data;
		m_data = newBlock;
		m_capacity = newCap;
	}

	T* m_data = nullptr;
	size_t m_size;
	size_t m_capacity;
};
