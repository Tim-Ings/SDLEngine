#pragma once
#include <SDL\SDL.h>
#include <sstream>
#include <memory>
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
	void SetTargetFps(float maxFrameRate) { maxFps = maxFrameRate; }
	std::string GetWindowTitleFormat() { return windowTitleFormat; }
	void SetWindowTitleFormat(std::string format) { windowTitleFormat = format; }
	void SetWindow(SDL_Window* window) { this->window = window; };
	float GetCurrentFps() { return currentFps; }
	float GetAverageFps() { return averageFps; }
	float GetDeltaTime() { return deltaTime; }

private:
	float targetFrameDuration;
	float maxFps;
	float currentFps;
	float averageFps;
	int frameCount;
	float deltaTime;
	float windowTitleUpdatePeriod;
	std::string windowTitleFormat;
	SDL_Window* window;
	std::unique_ptr<Timer> frameTimer;
	std::unique_ptr<Timer> windowTitleUpdateTimer;
	char* titleBuffer;
};