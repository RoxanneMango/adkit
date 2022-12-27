#ifndef SET_H
#define SET_H

#include <iostream>
#include <array>

template< typename D, int S >
class Set
{
public:

	std::array<D, S> array;
	bool availableSpaces[S];

	Set()
	{
		for(int i = 0; i < S; ++i)
		{
			availableSpaces[i] = true;
		}
	}
	void add(D num)
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] == num)
				{
					return;
				}
			}
		}
		for(unsigned int i = 0; i < S; ++i)
		{
			if(availableSpaces[i])
			{
				array[i] = num;
				availableSpaces[i] = false;
				return;
			}
		}
	}
	void remove(D num)
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] == num)
				{
					array[i] = 0;
					availableSpaces[i] = true;
					return;
				}
			}
		}
	}
	bool contains(D num)
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] == num)
				{
					return true;
				}
			}
		}
		return false;
	}
	D max()
	{
		D x = getFirstElement();
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				if(array[i] > x)
				{
					x = array[i];
				}
			}
		}
		return x;
	}	
	void print()
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				std::cout << array[i] << ' ';
			}
		}
	}
	
	D getFirstElement()
	{
		for(unsigned int i = 0; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				return array[i];
			}
		}		
		return array[0];
	}

	bool operator > (std::array<D, S> & set)
	{
		D sum1 = set.getFirstElement();
		D sum2 = getFirstElement();
		for(int i = 1; i < S; ++i)
		{
			if(!availableSpaces[i])
			{
				sum1 += set.array[i];
			}
			if(!set.availableSpaces[i])
			{
				sum2 += array[i];
			}
		}
		return (sum1 > sum2);
	}
	
};

#endif // SET_H