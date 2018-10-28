#include "OrderedSet.h"
#include "MySet.h"

int* OrderedSet::begin() const
{
	return Set::begin() + m_start;
}

OrderedSet OrderedSet::getSmaller(int cutoff) const {
	for (size_t i(0); i < m_size; i++) {
		if ((*this)[i] >= cutoff) return OrderedSet(begin(), i);
	} return OrderedSet(*this);
}

OrderedSet OrderedSet::getLarger(int cutoff) const {
	for (size_t i(0); i < m_size; i++) {
		if ((*this)[i] > cutoff) return OrderedSet(begin() + i, m_size - i);
	} return OrderedSet();
}

Set OrderedSet::merge(const Set& set) const
{
	const OrderedSet* os = dynamic_cast<const OrderedSet*>(&set);
	if (os)
	{
		size_t size = m_size + (*os).m_size;
		OrderedSet s(m_size + (*os).m_size);
		int j = 0;
		int k = 0;
		for (int i = 0; i < size; i++)
		{
			if (j >= m_size)
			{
				s.begin()[s.m_size++] = (*os).begin()[k];
				k++;
			}
			else if (k >= os->m_size)
			{
				s.begin()[s.m_size++] = begin()[j];
				j++;
			}
			else if (begin()[j] == (*os).begin()[k])
			{
				s.begin()[s.m_size++] = begin()[j];
				j++;
				k++;
				i++;
			}
			else if (begin()[j] < (*os).begin()[k])
			{
				s.begin()[s.m_size++] = begin()[j];
				j++;
			}
			else
			{
				s.begin()[s.m_size++] = (*os).begin()[k];
				k++;
			}
		}
		return s;
	}
	else
	{
		return Set::merge(set);
	}
}
