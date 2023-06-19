#pragma once
#include <algorithm>

// Definition //////////////////////////////////////////////////////////////////////////////////////
template <typename K, typename V>
class HashTable
{
private:
	using HashNode = std::pair<K, V>;
	using HashNodePtr = HashNode*;

public:
	using ValueType = HashNode;

	HashTable();
	HashTable(int capacity);
	~HashTable();

	void insert(const K& key, V& value);

private:
	void resize(int capacity);

private:
	HashNodePtr* m_table;
	size_t m_capacity;
	size_t m_size;
	float m_load_factor = 0.4f;

	HashNode m_dummy;
};


// Implementation //////////////////////////////////////////////////////////////////////////////////
template<typename K, typename V>
HashTable<K, V>::HashTable()
	: m_capacity(2), m_size(0)
{
}

template<typename K, typename V>
HashTable<K, V>::HashTable(int capacity)
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

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
	delete[] m_table;
}

template<typename K, typename V>
void HashTable<K, V>::insert(const K& key, V& value)
{
}

template<typename K, typename V>
void HashTable<K, V>::resize(int capacity)
{
}


