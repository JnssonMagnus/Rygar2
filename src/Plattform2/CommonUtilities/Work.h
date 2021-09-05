#pragma once

class Work
{
public:
					Work();
	virtual			~Work();

	virtual void	DoWork() = 0;
	inline bool		IsDone() const;

protected:
	volatile bool	myDone;
};

bool Work::IsDone() const
{
	return myDone;
}