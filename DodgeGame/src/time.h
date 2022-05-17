#pragma once
#include <SDL.h>
#include <iostream>

class Timer
{
public:
	Timer();
	void start();
	void stop();
	Uint32 getTicks();
	bool isStarted();

private:
	Uint32 mStartTicks;
	bool mStarted;
};

