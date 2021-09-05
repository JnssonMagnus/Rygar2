#ifndef LESSERPOINTER_H
#define LESSERPOINTER_H

namespace CommonUtilities
{
	template<class T>
	class LesserPointer
	{
	public:
		bool operator()(const T* aFirst, const T* aSecond) const;
	private:
	};

	template<class T>
	bool LesserPointer<T>::operator()(const T* aFirst, const T* aSecond) const
	{
		return !((*aFirst) > (*aSecond));
	}
}

namespace CU = CommonUtilities;

#endif