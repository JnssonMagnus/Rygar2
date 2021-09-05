#pragma once
#include <assert.h>

namespace CommonUtilities
{
	template <typename Type, int SIZE>
	class StaticArray
	{
	public:
		StaticArray() = default;
		StaticArray(const StaticArray& aStaticArray);
		StaticArray(const std::initializer_list<Type>& aInitList);

		~StaticArray()= default;

		StaticArray& operator=(const StaticArray& aStaticArray);

		inline const Type& operator[](const int aIndex) const;
		inline Type& operator[](const int aIndex);

		inline int Size() const;

		inline void Insert(int aIndex, Type& aObject);
		inline void DeleteAll();
	private:
		Type myData[SIZE];
	};
}

namespace CommonUtilities
{

	template <typename Type, int SIZE>
	StaticArray<Type, SIZE>::StaticArray(const StaticArray& aStaticArray)
	{
		operator=(aStaticArray);
	}

	template <typename Type, int SIZE>
	StaticArray<Type, SIZE>::StaticArray(const std::initializer_list<Type>& aInitList)
	{
		assert(aInitList.size() <= SIZE && "Init list is to large for staticarray!");
		size_t i = 0;
		for (; i < aInitList.size(); ++i)
		{
			myData[i] = *(aInitList.begin() + i);
		}

		for (int fillIndex = i; fillIndex < SIZE; ++fillIndex)
		{
			myData[fillIndex] = *(aInitList.end() - 1);
		}
	}

	template <typename Type, int SIZE>
	StaticArray<Type, SIZE>& StaticArray<Type, SIZE>::operator=(const StaticArray& aStaticArray)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			myData[i] = aStaticArray.myData[i];
		}
		return *this;
	}

	template <typename Type, int SIZE>
	inline const Type& StaticArray<Type, SIZE>::operator[](const int aIndex) const
	{
		assert(aIndex >= 0 && aIndex < SIZE && "Incorrect index");
		return myData[aIndex];
	}

	template <typename Type, int SIZE>
	inline Type& StaticArray<Type, SIZE>::operator[](const int aIndex)
	{
		assert(aIndex >= 0 && aIndex < SIZE && "Incorrect index");
		return myData[aIndex];
	}

	template <typename Type, int SIZE>
	inline void StaticArray<Type, SIZE>::Insert(int aIndex, Type& aObject)
	{
		assert(aIndex >= 0 && aIndex < SIZE && "Incorrect index");
		for (int i = SIZE - 2; i >= aIndex; --i)
		{
			myData[i+1] = myData[i];
		}
		myData[aIndex] = aObject;
	}

	template <typename Type, int SIZE>
	inline int StaticArray<Type, SIZE>::Size() const
	{
		return SIZE;
	}

	template <typename Type, int SIZE>
	inline void StaticArray<Type, SIZE>::DeleteAll()
	{
		for (int i = 0; i < SIZE; i++)
		{
			delete myData[i];
			myData[i] = nullptr;
		}
	}
}

namespace CU = CommonUtilities;