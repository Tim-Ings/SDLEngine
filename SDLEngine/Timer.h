#pragma once
#include <SDL\SDL.h>


class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();

	int GetTicks();
	bool IsStarted() { return started; }
	bool IsPaused() { return paused; }

private:
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;
};