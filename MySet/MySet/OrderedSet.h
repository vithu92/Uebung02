#pragma once
# include "MySet.h"
# include <algorithm>

using namespace std;

class	OrderedSet : public Set
{
	size_t m_start;
protected:
	// protected Datenstruktur (erlaubt Vererbung)
	OrderedSet(size_t size): Set(size), m_start(0){}

public:
	OrderedSet()
		: Set(), m_start(0)
	{}

	OrderedSet(const OrderedSet& s)
		: Set(s), m_start(s.m_start)
	{
		int * beg = Set::begin();
		sort(beg, beg + m_size);
	}

	OrderedSet(const int* arr, size_t size)
		:Set(arr, size), m_start(0)
	{
		int * beg = Set::begin();
		sort(beg, beg + m_size);
	}
	OrderedSet(initializer_list <int>) {}

	~OrderedSet()
	{
		Set::~Set();
	}

	virtual Set merge(const Set& set) const override;



	virtual int* begin() const override;

	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) kleiner als x sind
	OrderedSet getSmaller(int x) const;
	// gibt eine neue Menge zurueck, die alle Elemente von this enthaelt,
	// die (strikt) groesser als x sind
	OrderedSet getLarger(int x) const;
};
