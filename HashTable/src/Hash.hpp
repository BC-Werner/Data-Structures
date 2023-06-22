#pragma once

template <typename K>
class Hash
{
public:
	size_t operator () (const K& key) { return static_cast<size_t>(key); }
};
