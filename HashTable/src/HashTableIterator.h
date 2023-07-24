#pragma once

// Definition //////////////////////////////////////////////////////////////////////////////////////
template <typename Table>
class HashTableIterator
{
private:
	using ValueType     = typename Table::ValueType;
	using PointerType   = ValueType*;
	using ReferenceType = ValueType&;

	PointerType m_ptr;

public:
	HashTableIterator(PointerType ptr);
	HashTableIterator(const HashTableIterator& rhs);
	HashTableIterator(HashTableIterator&& rhs);

	ValueType         operator *  ()                                     { return *m_ptr; };
	HashTableIterator operator ++ ()                                     {}; // Pre  increment
	HashTableIterator operator ++ (int)                                  {}; // Post increment
	HashTableIterator operator -- ()                                     {}; // Pre  decrement
	HashTableIterator operator -- (int)                                  {}; // Post decrement
	bool              operator == (const HashTableIterator& other)       { return m_ptr == other.m_ptr; }
	bool              operator != (const HashTableIterator& other) const { return m_ptr != other.m_ptr; }
private:
};


// Implementation //////////////////////////////////////////////////////////////////////////////////
template<typename Table>
HashTableIterator<Table>::HashTableIterator(PointerType ptr)
	: m_ptr(ptr)
{
}

template<typename Table>
HashTableIterator<Table>::HashTableIterator(const HashTableIterator& rhs)
	: m_ptr(rhs.m_ptr)
{
}

template<typename Table>
HashTableIterator<Table>::HashTableIterator(HashTableIterator&& rhs)
{
}
