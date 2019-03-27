#include "stdafx.h"
#include "Timer.h"
#include "GameObject.h"

Timer::Timer()
{

}


Timer::~Timer()
{

}

void Timer::Awake()
{
	start = clock();
	alive = 0;
}

void Timer::Update()
{
	if (start + alive < clock())
		GetGameObject()->destroy = true;
}

void Timer::SetTimer(clock_t ms)
{
	alive = ms;
}
