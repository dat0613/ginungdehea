#pragma once

template <class T>

class Singleton
{
private:

	static T * instance;
public:
	Singleton() {  }
	~Singleton()
	{
		delete instance;
	}
	static T * GetInstance()
	{
		if (instance == 0)
			instance = new T;
		return instance;
	}
};

template <class T> T * Singleton<T>::instance = 0;