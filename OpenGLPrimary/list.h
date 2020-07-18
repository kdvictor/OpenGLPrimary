#pragma once
class List
{
public:
	void* mNext;
	template<typename T>
	T* Next()
	{
		return (T*)mNext;
	}
};