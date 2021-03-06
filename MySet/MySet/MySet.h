#pragma once
#include <memory>
#include <iostream>

using namespace std;

class Set
{
protected:
	size_t m_size;
	const shared_ptr<int[]> m_values;

	// protected Datenstruktur (erlaubt Vererbung)
	Set(size_t size)
		: m_values(new int[size], default_delete<int[]>()), m_size(0)
	{
		cout << "private-ctor " << endl;
	}

	// gesch�tzte Instanzmethoden
	virtual int *begin() const;

	int& operator[](size_t i) const;

	virtual Set merge(const Set& set) const;

	Set difference(const Set& set) const;

	Set difference(Set&& set);

	Set intersection(const Set& set) const;

	Set intersection(Set&& set) const;

public:
	// �ffentliche Methoden
		// Konstruktoren und Destruktor
	Set(): m_size(0) {}
	Set(const Set& s): m_size(s.m_size), m_values(s.begin()) {};

	Set(const int* arr, size_t size): Set(size)
	{
		for (size_t i = 0; i < size; i++) {
			if (!contains(*(arr + i))) {
				//*(m_values.get() + (m_size++)) = arr[i];
				(*this)[m_size++] = arr[i];
			}
		}
	}
	Set(initializer_list<int> list) : Set(list.begin(), list.size()) {}

	~Set() {
		cout << "public destructor " << endl;
	}

	//Instanzmethoden
	bool contains(int e) const;

	bool containsAll(const Set& set) const;

	bool isEmpty() const;

	size_t size() const;

	bool operator==(const Set& set) const { return containsAll(set) && set.containsAll(*this); }

	friend ostream& operator<<(ostream& os, const Set& s) {
		const int* const vptr = s.begin();
		os << "{";
		if (!s.isEmpty()) os << vptr[0];
		for (size_t i = 1; i < s.m_size; ++i) { os << ", " << vptr[i]; }
		os << "}";
		return os;
	}


	static Set merge(const Set& set1, const Set& set2) { return set1.merge(set2); }

	static Set difference(const Set& set1, const Set& set2) { return set2.difference(set1); }

	static Set intersection(const Set& set1, const Set& set2) { return set1.intersection(set2); }


	// Differenzmenge set1\set2
	static Set difference(Set&& set1, const Set& set2)
	{
		return set2.difference(move(set1));
	}

	static Set difference(Set&& set1, Set&& set2)
	{
		return set2.difference(move(set1));
	}

	// Schnittmenge
	static Set intersection(const Set& set1, Set&& set2)
	{
		return set1.intersection(move(set2));
	}
	static Set intersection(Set&& set1, const Set& set2)
	{
		return set2.intersection(move(set1));
	}
	static Set intersection(Set&& set1, Set&& set2)
	{
		return set1.intersection(move(set2));
	}
};

