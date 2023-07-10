#pragma once
#include <algorithm>
#include <cassert>
#include "Hash.hpp"
#include "HashTableIterator.h"

// Definition //////////////////////////////////////////////////////////////////////////////////////
template <typename K, typename V, typename F = Hash<K>>
class HashTable
{
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

	Iterator begin() const;
	Iterator end() const;

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

	HashNode m_dummy;
	HashNode m_end;
	HashFunctor hash;
};


// Implementation //////////////////////////////////////////////////////////////////////////////////
template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable()
	: m_capacity(2), m_size(0)
{
	m_table = new HashNodePtr[2];
	std::fill(m_table, m_table + m_capacity, nullptr);

	m_dummy = HashNode(K(-1), V(-1));
	m_end = HashNode(K(-1), V(-1));
}

template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(int capacity)
	: m_size(0)
{
	// Keep capacity at a power of two
	int power = static_cast<int>(ceil(log2(capacity)));
	m_capacity = static_cast<size_t>(pow(2, power));

	m_table = new HashNodePtr[m_capacity];
	std::fill(m_table, m_table + m_capacity, nullptr);

	m_dummy = HashNode(K(-1), V(-1));
	m_end = HashNode(K(-1), V(-1));
}

template<typename K, typename V, typename F>
inline HashTable<K, V, F>::HashTable(const HashTable& rhs)
{
	m_capacity = rhs.m_capacity;
	m_size = rhs.m_size;
	m_load_factor = rhs.m_load_factor;

	m_table = new HashNodePtr[m_capacity];
	std::fill(m_table, m_table + m_capacity, nullptr);

	m_dummy = HashNode(K(-1), V(-1));
	m_end = HashNode(K(-1), V(-1));

	for (int i = 0; i < rhs.m_capacity; i++)
	{
		if (rhs.m_table[i] && rhs.m_table[i] != rhs.m_dummy)
			insert(rhs.m_table[i]->first, rhs.m_table[i]->second);
	}
}

template<typename K, typename V, typename F>
inline HashTable<K, V, F>::HashTable(HashTable&& rhs)
	: m_table(std::move(rhs.m_table)),
	  m_capacity(std::move(rhs.m_capacity)),
	  m_size(std::move(rhs.m_size)),
	  m_load_factor(std::move(rhs.m_load_factor)),
	  m_dummy(std::move(rhs.m_dummy))
{
}

template<typename K, typename V, typename F>
HashTable<K, V, F>::~HashTable()
{
	clean();
	delete[] m_table;
}

template<typename K, typename V, typename F>
void HashTable<K, V, F>::insert(const K& key, V value)
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
		if (m_table[index] == &m_dummy)
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
void HashTable<K, V, F>::erase(const K& key)
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

	m_table[index] = &m_dummy;
	m_size--;
}

template<typename K, typename V, typename F>
bool HashTable<K, V, F>::empty() const
{
	return m_size == 0;
}

template<typename K, typename V, typename F>
HashTableIterator<HashTable<K, V, F>> HashTable<K, V, F>::begin() const
{
	if (empty())
	{
		return Iterator(&m_end);
	}

	int index = 0;
	HashNodePtr ptr = m_table[index];

	while (ptr == nullptr || ptr == &m_dummy)
	{
		if (index + 1 >= m_capacity)
		{
			return Iterator(&m_end);
		}

		ptr = m_table[++index];
	}

	return Iterator(ptr);
}

template<typename K, typename V, typename F>
HashTableIterator<HashTable<K, V, F>> HashTable<K, V, F>::end() const
{
	return Iterator(&m_end);
}

template<typename K, typename V, typename F>
void HashTable<K, V, F>::resize(int capacity)
{
	std::cout << "m_capacity: " << m_capacity << " new capacity: " << capacity << std::endl;
	assert(capacity > m_capacity);

	HashTable<K, V, F> other(capacity);

	for (int i = 0; i < m_capacity; i++)
	{
		if (m_table[i] != nullptr && m_table[i] != &m_dummy)
		{
			other.insert(m_table[i]->first, m_table[i]->second);
		}
	}

	swap(other);
}

template<typename K, typename V, typename F>
size_t HashTable<K, V, F>::probe(size_t x) const
{
	return ((x * x) + x) / 2;
}

template<typename K, typename V, typename F>
void HashTable<K, V, F>::swap(HashTable& rhs)
{
	std::swap(m_table, rhs.m_table);
	std::swap(m_capacity, rhs.m_capacity);
	std::swap(m_size, rhs.m_size);
	std::swap(m_load_factor, rhs.m_load_factor);
	std::swap(m_dummy, rhs.m_dummy);
	std::swap(hash, rhs.hash);
}

template<typename K, typename V, typename F>
void HashTable<K, V, F>::clean()
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
		if (m_table[i] && m_table[i] != &m_dummy)
			std::cout << m_table[i]->first << ", " << m_table[i]->second << " ";
		else
			std::cout << "_ ";
	}
	std::cout << std::endl;
}
