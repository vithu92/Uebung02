#pragma once
# include <memory>
# include <iostream>

using namespace std;

class Set
{
protected: 
	// Protected Datenstructure (erlaubt Vererbung)
	size_t m_size;
	shared_ptr<int[]> m_values;

	Set(size_t size) : m_values(new int[size]), m_size(0)
	{
		
		cout << "private-ctor " << endl;

	}

	int *begin() const;
	int& operator[](size_t i) const;
	Set merge(const Set& set) const;
	Set difference(const Set& set) const;
	Set intersection(const Set& set) const;

public: 
	//öffentliche Methoden
	
	//Standardkonstruktor ohne Argument
	Set(): m_size(0) {};

	//Kopierkonstruktur (shallow copy)
	Set(const Set& shallow) : m_size(shallow.m_size), m_values(shallow.m_values) {};

	//Typkonvertierungskonstruktor (deep copy)
	Set(const int* array, size_t size)
		: Set(size)
	{
		for (size_t i = 0; i < size; i++) {
			if (!contains(*(array + i))) {
				*(m_values.get() + (m_size++)) = array[i];
			}
		}
	}

	//Destruktor
	~Set() {
		m_values = nullptr;
		cout << "destructor" << endl;
	}

	//Instanzmethoden
	bool contains(int e) const;
	bool containsAll(const Set& set) const;
	bool isEmpty() const;
	size_t size() const;

	bool operator==(const Set& set) const
	{
		return containsAll(set) && set.containsAll(*this);
	}

	//Ausgabe-Operator für Output-Streams
	friend ostream& operator<<(ostream& os, const Set& set) {
		const int* const vptr = set.begin();
		os << "{";
		if (!set.isEmpty()) os << vptr[0];
		for (size_t i = 1; i < set.m_size; i++)
			{
				os << ", " << vptr[i];
			}
		os << "}";
		return os;

	//Klassen-Methoden

	//Vereinigungsmenge
		static Set merge(const Set& set1, const Set& set2)
		{
			return set1.merge(set2);
		}

	// Differenzmenge set1\set2
		static Set difference(const Set& set1, const Set& set2)
		{
			return set2.difference(set1);
		}

	// Schnittmenge
		static Set intersection(const Set& set1, const Set& set2)
		{
			return set1.intersection(set2);
		}
	}


};