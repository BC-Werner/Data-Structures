#pragma once
#include <algorithm>
#include <cassert>
#include "Hash.hpp"
#include "HashTableIterator.h"

// Definition //////////////////////////////////////////////////////////////////////////////////////
template <typename K, typename V, typename F = Hash<K>>
class HashTable
{
	template <typename Table>
	friend class HashTableIterator;

private:
	using HashNode = std::pair<K, V>;
	using HashNodePtr = HashNode*;
	using HashFunctor = F;

public:
	using ValueType = HashNode;
	using Iterator = HashTableIterator<HashTable<K, V, F>>;

	HashTable();
	HashTable(int capacity);
	HashTable(const HashTable& rhs);
	HashTable(HashTable&& rhs);
	~HashTable();

	void insert(const K& key, V value);
	void erase(const K& key);
	bool empty() const;

	Iterator begin();
	Iterator end();

	void _print() const; // To be deleted

private:
	void resize(int capacity);
	size_t probe(size_t x) const;
	void swap(HashTable& rhs);
	void clean();


private:
	HashNodePtr* m_table;
	size_t m_capacity;
	size_t m_size;
	float m_load_factor = 0.4f;

	static HashNode DUMMY;
	HashFunctor hash;
};

template<typename K, typename V, typename F>
std::pair<K, V> HashTable<K, V, F>::DUMMY = std::pair<K, V>(K(-1), V(-1));

// Implementation //////////////////////////////////////////////////////////////////////////////////
template<typename K, typename V, typename F>
inline HashTable<K, V, F>::HashTable()
	: m_capacity(2), m_size(0)
{
	m_table = new HashNodePtr[2];
	std::fill(m_table, m_table + m_capacity, nullptr);
}

template<typename K, typename V, typename F>
inline HashTable<K, V, F>::HashTable(int capacity)
	: m_size(0)
{
	// Keep capacity at a power of two
	int power = static_cast<int>(ceil(log2(capacity)));
	m_capacity = static_cast<size_t>(pow(2, power));

	m_table = new HashNodePtr[m_capacity];
	std::fill(m_table, m_table + m_capacity, nullptr);
}

template<typename K, typename V, typename F>
inline HashTable<K, V, F>::HashTable(const HashTable& rhs)
{
	m_capacity = rhs.m_capacity;
	m_size = rhs.m_size;
	m_load_factor = rhs.m_load_factor;

	m_table = new HashNodePtr[m_capacity];
	std::fill(m_table, m_table + m_capacity, nullptr);

	for (int i = 0; i < rhs.m_capacity; i++)
	{
		if (rhs.m_table[i] && rhs.m_table[i] != rhs.DUMMY)
			insert(rhs.m_table[i]->first, rhs.m_table[i]->second);
	}
}

template<typename K, typename V, typename F>
inline HashTable<K, V, F>::HashTable(HashTable&& rhs)
	: m_table(std::move(rhs.m_table)),
	  m_capacity(std::move(rhs.m_capacity)),
	  m_size(std::move(rhs.m_size)),
	  m_load_factor(std::move(rhs.m_load_factor))
{
}

template<typename K, typename V, typename F>
inline HashTable<K, V, F>::~HashTable()
{
	clean();
	delete[] m_table;
}

template<typename K, typename V, typename F>
inline void HashTable<K, V, F>::insert(const K& key, V value)
{
	if (m_size + 1 >= m_capacity * m_load_factor)
	{
		resize(m_capacity * 2);
	}

	HashNodePtr node = new HashNode(key, value);

	const size_t KEYHASH = hash(key) % m_capacity;

	size_t index = KEYHASH;
	int counter = 1;
	while (m_table[index] != nullptr && counter < m_capacity)
	{
		// Overrite dummy node if encountered
		if (m_table[index] == &DUMMY)
		{
			break;
		}

		// No duplicates
		if (m_table[index]->first == key)
		{
			delete node;
			return;
		}

		index = KEYHASH + probe(counter) % m_capacity;
		counter++;
	}

	m_table[index] = node;
	m_size++;
}

template<typename K, typename V, typename F>
inline void HashTable<K, V, F>::erase(const K& key)
{
	const size_t KEYHASH = hash(key) % m_capacity;
	size_t index = KEYHASH;
	int counter = 1;
	while (m_table[index] != nullptr && m_table[index]->first != key && counter < m_capacity)
	{
		index = KEYHASH + probe(counter) % m_capacity;
		counter++;
	}

	// Key not found
	if (counter == m_capacity)
	{
		return;
	}

	m_table[index] = &DUMMY;
	m_size--;
}

template<typename K, typename V, typename F>
inline bool HashTable<K, V, F>::empty() const
{
	return m_size == 0;
}

template<typename K, typename V, typename F>
inline typename HashTable<K,V,F>::Iterator HashTable<K, V, F>::begin()
{
	if (empty())
	{
		return end();
	}

	int index = 0;
	HashNodePtr ptr = m_table[index];

	while (ptr == nullptr || ptr == &DUMMY)
	{
		if (index + 1 >= m_capacity)
		{
			return end();
		}

		ptr = m_table[++index];
	}

	return Iterator(ptr);
}

template<typename K, typename V, typename F>
inline typename HashTable<K,V,F>::Iterator HashTable<K, V, F>::end()
{
	return Iterator(*(m_table + m_capacity));
}

template<typename K, typename V, typename F>
inline void HashTable<K, V, F>::resize(int capacity)
{
	assert(capacity > m_capacity);

	HashTable<K, V, F> other(capacity);

	for (int i = 0; i < m_capacity; i++)
	{
		if (m_table[i] != nullptr && m_table[i] != &DUMMY)
		{
			other.insert(m_table[i]->first, m_table[i]->second);
		}
	}

	swap(other);
}

template<typename K, typename V, typename F>
inline size_t HashTable<K, V, F>::probe(size_t x) const
{
	return ((x * x) + x) / 2;
}

template<typename K, typename V, typename F>
inline void HashTable<K, V, F>::swap(HashTable& rhs)
{
	std::swap(m_table, rhs.m_table);
	std::swap(m_capacity, rhs.m_capacity);
	std::swap(m_size, rhs.m_size);
	std::swap(m_load_factor, rhs.m_load_factor);
	std::swap(hash, rhs.hash);
}

template<typename K, typename V, typename F>
inline void HashTable<K, V, F>::clean()
{
	for (int i = 0; i < m_capacity; i++)
	{
		if (m_table[i] != nullptr)
		{
			delete m_table[i];
		}
	}
}

template<typename K, typename V, typename F>
inline void HashTable<K, V, F>::_print() const
{
	for (int i = 0; i < m_capacity; i++)
	{
		if (m_table[i] && m_table[i] != &DUMMY)
			std::cout << "[" << m_table[i]->first << " -> " << m_table[i]->second << "] ";
		else
			std::cout << "[ ] ";
	}
	std::cout << std::endl;
}
