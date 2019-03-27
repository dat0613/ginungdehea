#pragma once
#include "Component.h"
#include <ctime>
class Timer : public Component
{
private:

	clock_t start;
	clock_t alive;

public:
	Timer();
	~Timer();
	void Awake();
	void Update();
	void SetTimer(clock_t ms);
};

