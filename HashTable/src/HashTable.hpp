#pragma once
#include <algorithm>
#include "Hash.hpp"

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

	HashTable();
	HashTable(int capacity);
	HashTable(const HashTable& rhs);
	HashTable(HashTable&& rhs);
	~HashTable();

	void insert(const K& key, V& value);

private:
	void resize(int capacity);
	size_t probe(size_t x) const;

private:
	HashNodePtr* m_table;
	size_t m_capacity;
	size_t m_size;
	float m_load_factor = 0.4f;

	HashNode m_dummy;
	HashFunctor hash;
};


// Implementation //////////////////////////////////////////////////////////////////////////////////
template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable()
	: m_capacity(2), m_size(0)
{
}

template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(int capacity)
	: m_size(0)
{
	// Keep capacity at a power of two
	int power = static_cast<int>(ceil(log2(capacity)));
	m_capacity = static_cast<size_t>(pow(2, power));

	// Allow user to specify a resize function to match hash function?
	//resize(capacity);

	m_table = new HashNodePtr[capacity];
	std::fill(m_table, m_table + m_capacity, nullptr);
	m_dummy = HashNode(K(-1), V(-1));
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
	delete[] m_table;
}

template<typename K, typename V, typename F>
void HashTable<K, V, F>::insert(const K& key, V& value)
{
	HashNodePtr node = new HashNode(key, value);

	const size_t KEYHASH = hash(key) % m_capacity;

	size_t index = KEYHASH;
	int counter = 1;
	while (m_table[index] != nullptr && counter < m_capacity)
	{
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
void HashTable<K, V, F>::resize(int capacity)
{
}

template<typename K, typename V, typename F>
size_t HashTable<K, V, F>::probe(size_t x) const
{
	return ((x * x) + x) / 2;
}
