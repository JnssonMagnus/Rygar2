#pragma once
#include <assert.h>

namespace CommonUtilities
{
	template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<Type>& aInitList);

		~VectorOnStack();

		VectorOnStack & operator=(const VectorOnStack& aVectorOnStack);

		inline const Type& operator[](const CountType aIndex) const;
		inline Type& operator[](const CountType aIndex);

		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, const Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);

		void		Resize(const CountType aNewSize);

		inline void Clear();
		inline void DeleteAll();

		__forceinline CountType Size() const;
	private:
		Type myData[MaxSize];
		CountType myCurrentSize;
		bool myUseSafeModeFlag;
	};

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Resize(const CountType aNewSize)
	{
		myCurrentSize = aNewSize;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack()
	{
		myCurrentSize = 0;
		myUseSafeModeFlag = UseSafeModeFlag;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack(const std::initializer_list<Type>& aInitList)
	{
		assert(aInitList.size() <= MaxSize && "Init list is to large for VectorOnStack!");
		myCurrentSize = static_cast<CountType>(aInitList.size());
		CountType i = 0;
		for (; i < static_cast<CountType>(aInitList.size()); ++i)
		{
			myData[i] = *(aInitList.begin() + i);
		}
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		operator=(aVectorOnStack);
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		myCurrentSize = 0;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>& VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
	{
		myCurrentSize = aVectorOnStack.Size();
		myUseSafeModeFlag = aVectorOnStack.myUseSafeModeFlag;

		if (myUseSafeModeFlag == true)
		{
			for (CountType i = 0; i < myCurrentSize; ++i)
			{
				myData[i] = aVectorOnStack.myData[i];
			}
		}
		else
		{
			memcpy(this, &aVectorOnStack, sizeof(aVectorOnStack));
		}

		return *this;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline const Type& VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType aIndex) const
	{
		assert(aIndex >= 0 && "Index has to be 0 or more.");
		assert(aIndex < myCurrentSize && "a index out of bounds!");
		return myData[aIndex];
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline Type& VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType aIndex)
	{
		assert(aIndex >= 0 && "Index has to be 0 or more.");
		assert(aIndex < myCurrentSize && "a index out of bounds!");
		return myData[aIndex];
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Add(const Type& aObject)
	{
		assert(myCurrentSize < MaxSize && "Vector overflow (too many Add)");
		myData[myCurrentSize] = aObject;
		++myCurrentSize;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Insert(CountType aIndex, const Type& aObject)
	{
		assert(aIndex >= 0 && "Index has to be 0 or more.");
		assert(aIndex <= myCurrentSize && "a index out of bounds!");
		assert(myCurrentSize + 1 < MaxSize && "VectorOnStack is full! Can't insert.");
		for (CountType i = MaxSize - 2; i >= aIndex; --i)
		{
			myData[i + 1] = myData[i];
		}
		myData[aIndex] = aObject;
		++myCurrentSize;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::DeleteCyclic(Type& aObject)
	{
		for (CountType index = 0; index < myCurrentSize; ++index)
		{
			if (myData[index] == aObject)
			{
				DeleteCyclicAtIndex(index);
				return;
			}
		}

		assert("Object not found.");
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber < myCurrentSize && "Index out of bounds.");
		delete myData[aItemNumber];
		myData[aItemNumber] = myData[myCurrentSize - 1];
		myData[myCurrentSize - 1] = nullptr;
		--myCurrentSize;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::RemoveCyclic(const Type& aObject)
	{
		for (CountType i = 0; i < myCurrentSize; ++i)
		{
			if (myData[myCurrentSize] == aObject)
			{
				RemoveCyclicAtIndex(i);
				return;
			}
		}
		assert("Object not found.");
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber < myCurrentSize && "Index out of bounds.");
		myData[aItemNumber] = myData[myCurrentSize - 1];
		--myCurrentSize;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Clear()
	{
		myCurrentSize = 0;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::DeleteAll()
	{
		for (CountType i = 0; i < myCurrentSize; ++i)
		{
			delete myData[i];
			myData[i] = nullptr;
		}
		myCurrentSize = 0;
	}

	template <typename Type, int MaxSize, typename CountType, bool UseSafeModeFlag>
	__forceinline CountType VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Size() const
	{
		return myCurrentSize;
	}
}

namespace CU = CommonUtilities;