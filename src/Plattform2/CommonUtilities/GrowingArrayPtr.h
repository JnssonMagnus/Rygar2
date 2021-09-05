#pragma once

namespace CommonUtilities
{	
	template<class T, int size>
	class DllAPI GrowingArray<T*, size>
	{
	public:
		GrowingArray();
		GrowingArray(const GrowingArray &aGrowingArray);
		GrowingArray(GrowingArray &&aGrowingArray);
		~GrowingArray();
		void				operator=(const GrowingArray &aGrowingArray);
		void				operator=(GrowingArray &&aGrowingArray);
		inline T&			operator[](const int &aIndex);
		const inline T&		operator[](const int &aIndex) const;
		const T&			GetLast() const;
		T&					GetLast();
		void				Reserve(int aReservationSize);
		void				Resize(int aNewSize);
		void				Add(const T &aValue);
		void				SetSafeMode(const bool aSafeMode);

		template<typename C>
		void				AddSorted(const T &aValue, const C& aComparer);
		void				Insert(const T &aValue, const int aIndex);
		void				Remove(const T &aValue);
		void				Remove(const int aIndex);
		void				RemoveCyclic(const T &aValue);
		void				RemoveCyclicAtIndex(const int aIndex);

		
		void				DeleteCyclicAtIndex(const int aIndex);
		void				DeleteAll();

		int					Find(const T &aValue) const;
		void				Clear();
		const inline int	Size() const;
		T					pop_back();
	private:
		T*					myArray;
		int					myArraySize;
		int					myArrayPosition;
		bool				mySafeMode;
	};

#ifdef DLLEXPORT

	template<class T, int size>
	template<typename C>
	void GrowingArray<T*, size>::AddSorted(const T& aValue, const C& aComparer)
	{
		int i = 0;
		while (i < myArrayPosition && aComparer(myArray[i], aValue) && ++i);
		Insert(aValue, i);
	}

	template<class T, int size>
	T& GrowingArray<T*, size>::GetLast()
	{
		assert(myArrayPosition > 0 && "Can't get last, array is empty!");
		return myArray[myArrayPosition-1];
	}

	template<class T, int size>
	const T& GrowingArray<T*, size>::GetLast() const
	{
		assert(myArrayPosition > 0 && "Can't get last, array is empty!");
		return myArray[myArrayPosition-1];
	}

	template<class T, int size>
	void GrowingArray<T*, size>::SetSafeMode(const bool aSafeMode)
	{
		mySafeMode = aSafeMode;
	}

	template<class T, int size>
	void GrowingArray<T*, size>::Insert(const T &aValue, const int aIndex)
	{
		assert(aIndex <= myArrayPosition && aIndex >= 0 && "Index out of bounds when trying to insert value!");
		if (myArrayPosition + 1 >= myArraySize)
		{
			Reserve(myArraySize * 2);
		}
		++myArrayPosition;

		for (int i = myArrayPosition - 1; i >= aIndex; --i)
		{
			(*this)[i + 1] = (*this)[i];
		}

		(*this)[aIndex] = aValue;
	}

	template<class T, int size>
	void GrowingArray<T*, size>::operator=(const GrowingArray &aGrowingArray)
	{
		if (myArraySize < aGrowingArray.myArraySize)
		{
			delete[] myArray;
			myArray = nullptr;
			myArray = new T[aGrowingArray.myArraySize];
		}

		myArrayPosition = aGrowingArray.myArrayPosition;
		mySafeMode = aGrowingArray.mySafeMode;
		myArraySize = aGrowingArray.myArraySize;

		if (mySafeMode == true)
		{
			for (int i = 0; i < myArrayPosition; ++i)
			{
				myArray[i] = aGrowingArray[i];
			}
		}
		else
		{
			memcpy(myArray, aGrowingArray.myArray, sizeof(T) * myArrayPosition);
		}
	}

	template<class T, int size>
	void GrowingArray<T*, size>::operator=(GrowingArray &&aGrowingArray)
	{
		delete[] myArray;
		memcpy(this, &aGrowingArray, sizeof(aGrowingArray));

		aGrowingArray.myArray = nullptr;
		aGrowingArray.myArraySize = 0;
		aGrowingArray.myArrayPosition = 0;
	}

	template<class T, int size>
	GrowingArray<T*, size>::GrowingArray(const GrowingArray &aGrowingArray)
	{
		myArray = nullptr;
		myArraySize = 0;
		this->operator=(aGrowingArray);
	}

	template<class T, int size>
	GrowingArray<T*, size>::GrowingArray(GrowingArray &&aGrowingArray)
	{
		myArray = nullptr;
		operator=(std::move(aGrowingArray));
	}

	template<class T, int size>
	GrowingArray<T*, size>::GrowingArray()
	{
		static_assert(size > 0 && "Size must be larger than 0!");
		myArraySize = size;
		myArrayPosition = 0;
		mySafeMode = true;
		myArray = new T[myArraySize];
	}

	template<class T, int size>
	GrowingArray<T*, size>::~GrowingArray()
	{
		delete[] myArray;
		myArray = nullptr;
		myArraySize = 0;
		myArrayPosition = 0;
	}

	template<class T, int size>
	int GrowingArray<T*, size>::Find(const T &aValue) const
	{
		for (int i = 0; i < myArrayPosition; ++i)
		{
			if (myArray[i] == aValue)
			{
				return i;
			}
		}

		return -1;
	}

	template<class T, int size>
	void GrowingArray<T*, size>::RemoveCyclicAtIndex(const int aIndex)
	{
		assert(aIndex <= myArrayPosition && aIndex >= 0 && "RemoveCyclic: Index out of bounds!");
		if (mySafeMode == true)
		{
			myArray[aIndex] = myArray[--myArrayPosition];
		}
		else
		{
			memcpy(&myArray[aIndex], &myArray[--myArrayPosition], sizeof(T));
		}
	}

	template<class T, int size>
	void GrowingArray<T*, size>::DeleteCyclicAtIndex(const int aIndex)
	{
		assert(aIndex <= myArrayPosition && aIndex >= 0 && "DeleteCyclic: Index out of bounds!");
		delete myArray[aIndex];
		RemoveCyclicAtIndex(aIndex);
	}

	template<class T, int size>
	void GrowingArray<T*, size>::RemoveCyclic(const T &aValue)
	{
		int index = Find(aValue);
		assert(index <= myArrayPosition && index >= 0 && "RemoveCyclic: Value not found!");
		RemoveCyclicAtIndex(index);
	}

	template<class T, int size>
	void GrowingArray<T*, size>::DeleteAll()
	{
		for (int i = 0; i < myArrayPosition; ++i)
		{
			delete myArray[i];
			myArray[i] = nullptr;
		}

		Clear();
	}

	template<class T, int size>
	T GrowingArray<T*, size>::pop_back()
	{
		assert(myArrayPosition > 0 && "No item to pop!");
		--myArrayPosition;
		return myArray[myArrayPosition + 1];
	}

	template<class T, int size>
	void GrowingArray<T*, size>::Clear()
	{
		myArrayPosition = 0;
	}

	template<class T, int size>
	const int GrowingArray<T*, size>::Size() const
	{
		return myArrayPosition;
	}

	template<class T, int size>
	T& GrowingArray<T*, size>::operator[](const int &aIndex)
	{
		assert(aIndex <= myArrayPosition && aIndex >= 0 && "Out of bounds!");
		return myArray[aIndex];
	}

	template<class T, int size>
	const T& GrowingArray<T*, size>::operator[](const int &aIndex) const
	{
		assert(aIndex <= myArrayPosition && aIndex >= 0 && "Out of bounds!");
		return myArray[aIndex];
	}

	template<class T, int size>
	void GrowingArray<T*, size>::Reserve(int aReservationSize)
	{
		if (aReservationSize > myArraySize)
		{
			T* oldArray = myArray;
			myArray = new T[aReservationSize];

			if (mySafeMode == true)
			{
				for (int i = 0; i < myArrayPosition; ++i)
				{
					myArray[i] = oldArray[i];
				}
			}
			else
			{
				memcpy(myArray, oldArray, sizeof(T) * myArrayPosition);
			}

			delete[] oldArray;

			myArraySize = aReservationSize;
		}
	}

	template<class T, int size>
	void GrowingArray<T*, size>::Resize(int aSize)
	{
		assert(aSize >= 0 && "Resize size must be >= 0");
		if (aSize >= myArraySize)
		{
			Reserve(aSize);
		}

		myArrayPosition = aSize;
	}

	template<class T, int size>
	void GrowingArray<T*, size>::Add(const T &aValue)
	{
		if (myArrayPosition >= myArraySize)
		{
			Reserve(myArraySize * 2);
		}

		myArray[myArrayPosition++] = aValue;
	}

	template<class T, int size>
	void GrowingArray<T*, size>::Remove(const T &aValue)
	{
		int index = Find(aValue);
		assert(index != -1 && "Value to remove not found in growingArray!");
		Remove(index);
	}

	template<class T, int size>
	void GrowingArray<T*, size>::Remove(const int aIndex)
	{
		assert(aIndex >= 0 && aIndex < myArrayPosition);
		if (aIndex < myArrayPosition - 1)
		{
			if (mySafeMode == true)
			{
				for (int index = aIndex; index < myArrayPosition; ++index)
				{
					myArray[index] = myArray[index + 1];
				}
			}
			else
			{
				memcpy(myArray + aIndex, myArray + aIndex + 1, sizeof(T) * (myArrayPosition - aIndex));
			}
		}

		--myArrayPosition;
	}

#endif
}

namespace CU = CommonUtilities;