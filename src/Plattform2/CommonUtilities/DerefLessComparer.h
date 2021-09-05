#pragma once

template<typename T>
struct DerefLessComparer
{
	bool operator()(T aObject, T aSecondObject) const
	{
		return ((*aSecondObject) > (*aObject));
	}
};