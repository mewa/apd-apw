#pragma once
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

template <typename SizeT, typename ValueT>
class Backpack
{
public:
	Backpack(size_t, size_t);
	~Backpack();

	ValueT const& valueOf(size_t) const;
	SizeT const& sizeOf(size_t) const;

	void print() const;

	size_t n;
	size_t size;
	vector<ValueT> values;
	vector<SizeT> sizes;
};

template <typename SizeT, typename ValueT>
Backpack<SizeT, ValueT>::Backpack(size_t n, size_t size) {
	this->n = n;
	this->size = size;
}

template <typename SizeT, typename ValueT>
Backpack<SizeT, ValueT>::~Backpack() {
}

template <typename SizeT, typename ValueT>
ValueT const& Backpack<SizeT, ValueT>::valueOf(size_t i) const {
	assert(i > 0);
	return values[i - 1];
}

template <typename SizeT, typename ValueT>
SizeT const& Backpack<SizeT, ValueT>::sizeOf(size_t i) const {
	assert(i > 0);
	return sizes[i - 1];
}

template <typename SizeT, typename ValueT>
void Backpack<SizeT, ValueT>::print() const {
	cout << "n: " << n << "\tsize: " << size << endl;
}

