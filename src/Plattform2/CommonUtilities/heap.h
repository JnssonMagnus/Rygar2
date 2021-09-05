#pragma once

#include "growingarray.h"
#include <vector>
#include <functional>
#include <assert.h>
#include <cmath>

namespace CommonUtilities
{

	#define RIGHT_CHILD static_cast<int>(pos * 2 + 2)
	#define LEFT_CHILD static_cast<int>(pos * 2 + 1)
	#define PARENT (pos - 1)/2

	template<class T, class Compare = std::greater<T> >
	class Heap
	{
	public:
		virtual void			Enqueue		(const T &someData);
		T						Dequeue		(void);
		T						Top			(void);

								Heap		();
								Heap		(const std::vector<T>& aVector);
		inline bool				IsEmpty		() const;
		void					Clear		();
		void					ResortHeap	();
		void					DeleteAll   ();

	private:
		Compare					myCompare;
		CU::GrowingArray<T>		myGrowingArray;
	};

	template<class T, class Compare>
	Heap<T, Compare>::Heap()
	{
	}

	template<class T, class Compare>
	Heap<T, Compare>::Heap(const std::vector<T>& aVector)
	{
		for (int i = 0; i < aVector.length(); i++)
		{
			myGrowingArray.add(aVector[i]);
		}

		ResortHeap();
	}

	template<class T, class Compare>
	void Heap<T, Compare>::Clear()
	{
		myGrowingArray.Clear();
	}

	template<class T, class Compare>
	void Heap<T, Compare>::DeleteAll()
	{
		while (IsEmpty() == false)
		{
			delete Dequeue();
		}
	}

	template<class T, class Compare>
	void Heap<T, Compare>::ResortHeap()
	{
		int pos = myGrowingArray.Size() - 1;
		for (int i = PARENT; i >= 0; i--)
		{
			pos = i;
			while (true)
			{
				if (RIGHT_CHILD < myGrowingArray.Size())
				{
					if (myCompare(myGrowingArray[LEFT_CHILD], myGrowingArray[pos]) 
						|| myCompare(myGrowingArray[RIGHT_CHILD], myGrowingArray[pos]))
					{
						// if left node is larger/smaller than right node
						if (myCompare(myGrowingArray[LEFT_CHILD], myGrowingArray[RIGHT_CHILD]))
						{
							std::swap(myGrowingArray[LEFT_CHILD], myGrowingArray[pos]);
							pos = LEFT_CHILD;
						}
						else
						{
							std::swap(myGrowingArray[RIGHT_CHILD], myGrowingArray[pos]);
							pos = RIGHT_CHILD;
						}
					}
					else
					{
						break;
					}
				}
				else if (LEFT_CHILD < myGrowingArray.Size())
				{
					if (myCompare(myGrowingArray[LEFT_CHILD], myGrowingArray[pos]))
					{
						std::swap(myGrowingArray[LEFT_CHILD], myGrowingArray[pos]);
						pos = LEFT_CHILD;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}

		//PrintHeap();
	}

	template<class T, class Compare>
	bool Heap<T, Compare>::IsEmpty() const
	{
		return (myGrowingArray.Size() < 1);
	}

	template<class T, class Compare>
	void Heap<T, Compare>::Enqueue(const T &someData)
	{
		myGrowingArray.Add(someData);
		int pos = myGrowingArray.Size() - 1;
		while (pos > 0 && myCompare(myGrowingArray[pos], myGrowingArray[PARENT]))
		{
			std::swap(myGrowingArray[pos], myGrowingArray[PARENT]);
			pos = PARENT;
		}
	}

	template<class T, class Compare>
	T Heap<T, Compare>::Dequeue()
	{
		assert (myGrowingArray.Size() && "Heap is empty");

		T value = myGrowingArray[0];
	
		myGrowingArray[0] = myGrowingArray[myGrowingArray.Size() - 1];
		myGrowingArray.pop_back();

		int pos = 0;
	
		while (true)		
		{
			// if not at leaf level, normal case, check both childs
			if (RIGHT_CHILD < myGrowingArray.Size())
			{
				// Check if was smaller than any of its children
				if ( myCompare(myGrowingArray[LEFT_CHILD], myGrowingArray[pos]) ||
					myCompare(myGrowingArray[RIGHT_CHILD], myGrowingArray[pos]) )
				{
					// check which child was largest
					if (myCompare(myGrowingArray[RIGHT_CHILD], myGrowingArray[LEFT_CHILD]))
					{
						std::swap(myGrowingArray[pos], myGrowingArray[RIGHT_CHILD]);
						pos = LEFT_CHILD;
					}
					else 
					{
						std::swap(myGrowingArray[pos], myGrowingArray[LEFT_CHILD]);
						pos = RIGHT_CHILD;
					}
				}
				else
				{
					break;
				}
			}
			// if at leaf level, and has one leaf
			else if (LEFT_CHILD < myGrowingArray.Size())
			{
				// check if smaller than only child
				if ( myCompare(myGrowingArray[LEFT_CHILD], myGrowingArray[pos]))
				{
					std::swap(myGrowingArray[pos], myGrowingArray[LEFT_CHILD]);
					pos = LEFT_CHILD;
				}
				else
				{
					break;
				}
			}
			else // has reached bottom level
			{
				break;
			}
		}

		return value;
	}

	template<class T, class Compare>
	T Heap<T, Compare>::Top()
	{
		return myGrowingArray[0];
	}

}

namespace CU = CommonUtilities;