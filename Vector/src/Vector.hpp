#pragma once

#include <initializer_list>

template<typename T>
class Vector
{
public:
	class Iterator
	{
	public:
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		Iterator(pointer p) : ptr(p) {}

		reference operator*() const { return *ptr; }
		pointer operator->() const { return ptr; }
		Iterator operator++() { ptr++; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		Iterator operator--() { ptr--; return *this; }
		Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
		Iterator operator+=(int n) { for (int i = 0; i < n; i++) ++(*this); return *this; }
		bool operator==(const Iterator& other) { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }

		pointer data() const { return ptr; }

	private:
		pointer ptr;
	};

	Vector()
		: m_size(0)
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

	Vector(Vector const& copy)
		: m_capacity(copy.m_capacity), m_size(0)
	{
		allocate(m_capacity);

		for (int loop = 0; loop < copy.m_size; ++loop)
			push_back(copy.m_data[loop]);
	}

	Vector(Vector&& move) noexcept
		: m_capacity(0), m_size(0), m_data(nullptr)
	{
		move.swap(*this);
	}

	~Vector() { delete[] m_data; m_data = nullptr; }

	Iterator erase(Iterator pos) 
	{
		if (empty()) return end();
		const Iterator newPos = pos;
		Iterator tmp = pos;
		tmp++;

		while (pos != end())
		{
			*pos = *tmp;
			pos++;
			tmp++;
		}
		m_size--;
		return newPos;
	};

	Iterator erase(const Iterator& first, const Iterator& last) 
	{
		if (empty()) return end();
		const Iterator toReturn = first;
		Iterator f = first;
		Iterator l = last;
		bool shouldDecrease = true;
		int count = 0;

		while (f != end())
		{
			if (f == last) shouldDecrease = false;
			if (shouldDecrease) count++;
			if (l != end())
			{
				*f = *l;
				l++;
			}
			f++;
		}

		m_size -= count;
		return toReturn;
	}

	Iterator insert(Iterator& pos, const T& data)
	{
		if (m_size + 1 > m_capacity) return insert_reallocate(pos, data);

		resize(m_size + 1);

		Iterator iter = end();
		Iterator prevIter = end();
		iter--;
		while (iter != begin() && iter != pos)
		{
			iter--;
			prevIter--;
			*prevIter = *iter;
		}

		prevIter--;
		*prevIter = data;

		return prevIter;
	}

	void resize(size_t count) 
	{
		if (count > m_capacity) { allocate(count); }
		if (m_size < count)
		{
			for (size_t i = m_size; i < count; i++)
			{
				m_data[i] = T();
			}
			m_size = count;
			return;
		}

		if (m_size > count) { m_size = count; allocate(m_capacity); }
	}

	void		push_back(const T& data)		{ if (m_size >= m_capacity) allocate(m_capacity * 2); m_data[m_size++] = data; };
	void		pop_back()						{ if (m_size > 0) resize(m_size - 1); };
	void		clear()							{ m_size = 0; allocate(m_capacity); };
	bool		empty() const					{ return m_size == 0; }
	size_t		size() const					{ return m_size; }
	size_t		capacity() const				{ return m_capacity; }
	void		reserve(size_t newCap)			{ if (newCap <= m_capacity) return; allocate(newCap); }
	void		shrink_to_fit()					{ if (m_size != m_capacity) allocate(m_size); }
	T&			at(size_t pos)					{ if (pos >= m_size || pos < 0) throw std::out_of_range("Invalid address."); return m_data[pos]; }
	const T&	at(size_t pos) const			{ if (pos >= m_size || pos < 0) throw std::out_of_range("Invalid address.");  return m_data[pos]; }
	T&			front()							{ return *begin(); }
	const T&	front() const					{ return *begin(); } 
	T&			back()							{ return *(--end()); }
	const T&	back() const					{ return *(--end()); }
	Iterator	begin()							{ return Iterator(&m_data[0]); }
	Iterator	end()							{ return Iterator(&m_data[m_size]); }
	Iterator	iterator_at(size_t i)			{ if (i < 0 || i >= m_size) throw std::out_of_range("Invalid address."); return Iterator(&m_data[i]); }
	T&			operator[](size_t index)		{ return m_data[index]; }
	const T&	operator[](size_t index) const	{ return m_data[index]; }

private:
	void allocate(size_t newCap)
	{
		T* newBlock = new T[newCap];

		if (newCap < m_size)
			m_size = newCap;

		for (size_t i = 0; i < m_size; i++)
			newBlock[i] = std::move(m_data[i]);

		delete[] m_data;
		m_data = newBlock;
		m_capacity = newCap;
	}

	void swap(Vector& other) noexcept
	{
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_size, other.m_size);
		std::swap(m_data, other.m_data);
	}

	Iterator insert_reallocate(Iterator& pos, const T& data)
	{
		Vector<T> newVector(*this);
		newVector.resize(newVector.size() + 1);

		Iterator iter = end();
		Iterator newIter = newVector.end();

		while (iter != begin() && iter != pos)
		{
			iter--;
			newIter--;

			*newIter = *iter;
		}

		newIter--;
		*newIter = data;

		swap(newVector);
		return newIter;
	}

	T* m_data = nullptr;
	size_t m_size;
	size_t m_capacity;
};
