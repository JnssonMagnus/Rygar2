#pragma once
#include <assert.h>
#include <new>
#ifdef _DEBUG
#include <vector>
#include <string>
#include <typeinfo>
#endif


namespace CommonUtilities
{
	template<class T>
	class VirtualSmartContainer
	{
	public:
					VirtualSmartContainer();
					VirtualSmartContainer(int aBufferSize);
					~VirtualSmartContainer();
		void		Init(int aBufferSize);
		void		Clear();
		inline int	Size();
		inline bool	Fits(size_t aObjectTypeSize);

		template <class DerivedClass>
		DerivedClass& Add(const DerivedClass& aDerivedClass);

		friend class Iterator;

		class Iterator
		{
		public:
			void operator++(int);
			bool IsAtEnd();
			bool IsAtBack();
			T* operator->();
			bool operator==(const Iterator& aIterator) const;
			bool operator!=(const Iterator& aIterator) const;
			Iterator(const VirtualSmartContainer& aParent);

			friend class VirtualSmartContainer;
		private:
			Iterator(const VirtualSmartContainer& aParent, int aCurrentItemIndex, int aBufferIndex);
			int	myCurrentItemIndex;
			int	myBufferIndex;
			const VirtualSmartContainer& myParent;
		};

		Iterator	End() const;


	private:
		char*		myData;
		int			myItemCount;
		int			myBufferSize;
		int			myUsedBufferSize;
#ifdef _DEBUG
		std::vector<std::string> myObjectTypeName;
#endif

	};

	template<class T>
	VirtualSmartContainer<T>::VirtualSmartContainer()
	{
		myData = nullptr;
		myItemCount = 0;
		myUsedBufferSize = 0;
		myBufferSize = 0;
	}

	template<class T>
	VirtualSmartContainer<T>::VirtualSmartContainer(int aBufferSize)
	{
		myData = nullptr;
		Init(aBufferSize);
	}

	template<class T>
	inline VirtualSmartContainer<T>::~VirtualSmartContainer()
	{
		Clear();
		myBufferSize = 0;
		delete[] myData;
		myData = nullptr;
	}

	template<class T>
	void VirtualSmartContainer<T>::Init(int aBufferSize)
	{
		assert(myData == nullptr && "VirtualSmartContainer already initiated!");
		myItemCount = 0;
		myUsedBufferSize = 0;
		myBufferSize = aBufferSize;
		myData = new char[aBufferSize];

	}

	template<class T>
	inline void VirtualSmartContainer<T>::Clear()
	{
		Iterator it(*this);
		while (it.IsAtEnd() == false)
		{
			it->~T();
			it++;
		}

		myItemCount = 0;
		myUsedBufferSize = 0;

#ifdef _DEBUG
		myObjectTypeName.clear();
#endif
	}

	template<class T>
	typename VirtualSmartContainer<T>::Iterator VirtualSmartContainer<T>::End() const
	{
		return Iterator(*this, myItemCount, myUsedBufferSize);
	}

	template<class T>
	inline int VirtualSmartContainer<T>::Size()
	{
		return myItemCount;
	}

	template<class T>
	inline bool VirtualSmartContainer<T>::Fits(size_t aObjectTypeSize)
	{
		return (myUsedBufferSize + static_cast<int>(aObjectTypeSize) + static_cast<int>(sizeof(short)) < myBufferSize);
	}

	template<class T>
	template<class DerivedClass>
	DerivedClass& VirtualSmartContainer<T>::Add(const DerivedClass& aDerivedClass)
	{
		static_assert(std::is_base_of<T, DerivedClass>::value == true, "Added class isn't derived of base class T");
		assert(myData != nullptr && "VirtualSmartContainer isn't inited!");
		assert(Fits(sizeof(DerivedClass)) == true && "VirtualSmartContainer is full!");
		// insert size of object as short
		*reinterpret_cast<short*>(&myData[myUsedBufferSize]) = static_cast<short>(sizeof(DerivedClass));
		myUsedBufferSize += sizeof(short);

		// add object
		new (reinterpret_cast<DerivedClass*>(&myData[myUsedBufferSize])) DerivedClass(aDerivedClass);
		myUsedBufferSize += sizeof(DerivedClass);

		++myItemCount;

#ifdef _DEBUG
		//myObjectTypeName.push_back(typeid(aDerivedClass).name());
#endif

		return *reinterpret_cast<DerivedClass*>(&myData[myUsedBufferSize - sizeof(DerivedClass)]);
	}	

	template<class T>
	inline void VirtualSmartContainer<T>::Iterator::operator++(int)
	{
		// read two first bytes = size of derived class at current position
		short size = *(reinterpret_cast<short*>(&myParent.myData[myBufferIndex]));
		this->myCurrentItemIndex++;
		this->myBufferIndex += sizeof(short) + size; // two is for the short containing the size
	}

	template<class T>
	inline bool VirtualSmartContainer<T>::Iterator::IsAtEnd()
	{
		return (this->myCurrentItemIndex >= myParent.myItemCount);
	}

	template<class T>
	inline bool VirtualSmartContainer<T>::Iterator::IsAtBack()
	{
		return (myCurrentItemIndex-1 == myParent.myItemCount-1);
	}

	template<class T>
	inline T* VirtualSmartContainer<T>::Iterator::operator->()
	{
		return reinterpret_cast<T*>(&myParent.myData[myBufferIndex+2]);
	}

	template<class T>
	inline bool VirtualSmartContainer<T>::Iterator::operator==(const Iterator& aIterator) const
	{
		assert(&aIterator.myParent == &myParent && "Iterators doesn't have same parents!");	
		return (aIterator.myCurrentItemIndex == myCurrentItemIndex && aIterator.myBufferIndex == myBufferIndex);
	}

	template<class T>
	inline bool VirtualSmartContainer<T>::Iterator::operator!=(const Iterator & aIterator) const
	{
		return !operator==(aIterator);
	}

	template<class T>
	inline VirtualSmartContainer<T>::Iterator::Iterator(const VirtualSmartContainer& aParent) : myParent(aParent)
	{
		myBufferIndex = 0;
		myCurrentItemIndex = 0;
	}

	template<class T>
	VirtualSmartContainer<T>::Iterator::Iterator(const VirtualSmartContainer& aParent, int aCurrentItemIndex, int aBufferIndex) : myParent(aParent)
	{
		myCurrentItemIndex = aCurrentItemIndex;
		myBufferIndex = aBufferIndex;
	}

};

namespace CU = CommonUtilities;
