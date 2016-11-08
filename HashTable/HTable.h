#pragma once
#include "SLList.h"
template <typename Type>
class HTable
{
private:
	SLList<Type>* table;
	unsigned int buckets;
	unsigned int(*hFunction)(const Type&v);

public:
	//Default constructor
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
	{
		buckets = numOfBuckets;
		table = new SLList<Type>[buckets];
		this->hFunction = hFunction;
	}

	//Default deconstructor
	~HTable() 
	{
		clear();
		//delete[] table;
	}

	//Assignment Operator
	HTable<Type>& operator=(const HTable<Type>& that)
	{
		delete[] table;
		table = new SLList<Type>[that.buckets];
		for (unsigned int i = 0; i < buckets; ++i)
			table[i] = that.table[i];
		hFunction = that.hFunction;
		return *this;
	}

	//Copy Constructor
	HTable(const HTable<Type>& that)
	{
		buckets = that.buckets;
		for (unsigned int i = 0; i < buckets; ++i)
			table[i] = that.table[i];
		hFunction = that.hFunction;
	}

	//Insert
	void insert(const Type& v)
	{
		unsigned int bucketNeeded = hFunction(v);
		table[bucketNeeded].addHead(v);
	}

	//Find and Remove
	bool findAndRemove(const Type& v)
	{
		SLLIter<Type> iter(table[hFunction(v)]);
		iter.begin();
		while (!iter.end())
		{
			if (iter.current() == v)
			{
				table[hFunction(v)].remove(iter);
				return true;
			}
			else
				++iter;
		}
		return false;
	}

	//Clear
	void clear()
	{
		for (unsigned int i = 0; i < buckets; ++i)
			table[i].clear();
	}

	//Find
	int find(const Type& v) const
	{
		SLLIter<Type> iter(table[hFunction(v)]);
		iter.begin();
		while (iter.end() == false)
		{
			if (iter.current() == v)
				return hFunction(v);
			else
				++iter;
		}
		return -1;
	}
};
