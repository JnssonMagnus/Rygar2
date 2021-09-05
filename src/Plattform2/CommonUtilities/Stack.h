#pragma once
#include "GrowingArray.h"
#include <Debugger/DL_Debug.h>

namespace CommonUtilities
{
	template<typename T>
	class Stack
	{
	public:
		Stack();
		~Stack();
		T&							Top();
		const T&					Top() const;
		void						Push(const T& aObject);
		void						Pop();
		int							Size() const;
		bool						Empty() const;

	private:
		CU::GrowingArray<T>			myData;
	};

	template<typename T>
	Stack<T>::Stack()
	{

	}

	template<typename T>
	Stack<T>::~Stack()
	{

	}

	template<typename T>
	T& Stack<T>::Top()
	{
		DL_ASSERT(myData.Size() > 0 && "Stack is empty!");
		return myData[myData.Size() - 1];
	}

	template<typename T>
	const T& Stack<T>::Top() const
	{
		DL_ASSERT(myData.Size() > 0 && "Stack is empty!");
		return myData[myData.Size() - 1];
	}

	template<typename T>
	void Stack<T>::Pop()
	{
		DL_ASSERT(myData.Size() > 0 && "Stack is empty!");
		myData.RemoveCyclicAtIndex(myData.Size() - 1);
	}

	template<typename T>
	int Stack<T>::Size() const
	{
		return myData.Size();
	}

	template<typename T>
	bool Stack<T>::Empty() const
	{
		return myData.Size() <= 0;
	}

	template<typename T>
	void Stack<T>::Push(const T& aObject)
	{
		myData.Add(aObject);
	}
}

namespace CU = CommonUtilities;