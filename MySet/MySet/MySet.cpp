#include "MySet.h"


using namespace std;

//Beginn methode
int* Set::begin() const {
	return m_values.get();
}

// Operator Methode - Mit Begin das erste Element und dann anzahl size_t addieren. 
int& Set::operator[](size_t i) const {
	return *(begin() + i);
}

// Merge Methode
Set Set::merge(const Set& set) const {
	// erstelle eine neue Menge mit allen Elementen von this
	Set result(m_size + set.m_size);
	std::memcpy(result.begin(), begin(), m_size * sizeof(int));
	result.m_size = m_size;
	// fuege nur jene Elemente von set dazu, die in this noch nicht enthalten sind
	for (size_t i = 0; i < set.m_size; ++i) {
		if (!contains(set[i])) result[result.m_size++] = set[i];
	}
	return result;
}

Set Set::difference(const Set& set) const {
	Set differenceSet(set.m_size);
	for (size_t i = 0; i < set.m_size; i++) {
		//durch jedes Element in set durchgehen und falls es noch nicht im differenceSet existiert, an der m_size index hinzufügen.		
		if (!contains(*(set.begin() + i))) {
			*(differenceSet.begin() + differenceSet.m_size++) = *(set.begin() + i);
		}
	}
	return differenceSet;
}

Set Set::intersection(const Set& set) const {
	cout << "hier" << endl;
	Set intersectionSet(set.m_size);
	for (size_t i = 0; i < set.m_size; i++) {
		if (contains(*(set.begin() + i))) {
			*(intersectionSet.begin() + intersectionSet.m_size++) = *(set.begin() + i);
		}
	}
	return intersectionSet;

}

bool Set::contains(const int value) const
{
	bool exist = false;

	for (size_t i = 0; i < size(); ++i) {
		if (begin()[i] == value) {
			exist = true;
			break;
		}
	}

	return exist;
}

bool Set::containsAll(const Set& set) const
{
	bool exist = true;

	for (size_t i = 0; i < set.size(); ++i) {
		if (!contains(set[i])) {
			exist = false;
			break;
		}
	}

	return exist;
}

bool Set::isEmpty() const {
	return m_size == 0;
}

size_t Set::size() const {
	return m_size;
}