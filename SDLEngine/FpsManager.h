#pragma once
#include <SDL\SDL.h>
#include <chrono>
#include <thread>
#include <sstream>
#include "Timer.h"

class FpsManager
{
public:
	FpsManager(int maxFrameRate);
	~FpsManager();

	void Update();

	float GetWindowTitleUpdatePeriod() { return windowTitleUpdatePeriod; }
	void SetWindowTitleUpdatePeriod(float ms) { windowTitleUpdatePeriod = ms; }
	float GetTargetFps() { return maxFps; }
	// settings this to -1 disables updating the window title with the frame rate
	void SetTargetFps(float maxFrameRate) { maxFps = maxFrameRate; }
	std::string GetWindowTitleFormat() { return windowTitleFormat; }
	void SetWindowTitleFormat(std::string format) { windowTitleFormat = format; }
	void SetWindow(SDL_Window* window) { this->window = window; };

	float GetDeltaTime() { return deltaTime; }

private:
	float targetFrameDuration;
	float maxFps;
	float currentFps;
	int frameCount;
	float deltaTime;
	float windowTitleUpdatePeriod;
	float lastWindowTitleUpdate;
	std::string windowTitleFormat;
	SDL_Window* window;
	Timer* frameTimer;
	Timer* windowTitleUpdateTimer;
	char* titleBuffer;
};