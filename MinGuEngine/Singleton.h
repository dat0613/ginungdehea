#pragma once

template <class T>

class Singleton
{
private:

	static T * inst;

public:

	Singleton()
	{

	}
	virtual ~Singleton()
	{
		delete inst;
	}

	static T * get()
	{
		if (inst == 0)
			inst = new T();
		return inst;
	}
};

template <class T>
T * Singleton<T>::inst = 0;