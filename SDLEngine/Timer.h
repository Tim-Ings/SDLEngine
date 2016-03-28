#pragma once


class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();

	int GetTicks() const;
	inline bool IsStarted() const { return started; }
	inline bool IsPaused() const { return paused; }

private:
	int startTicks;
	int pausedTicks;
	bool paused;
	bool started;
};