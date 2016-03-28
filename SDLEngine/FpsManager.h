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

	inline void SetWindowTitleUpdatePeriod(float ms) { windowTitleUpdatePeriod = ms; }
	inline void SetTargetFps(float maxFrameRate) { maxFps = maxFrameRate; }
	inline void SetWindowTitleFormat(std::string format) { windowTitleFormat = format; }
	inline void SetWindow(SDL_Window* window) { this->window = window; }
	inline std::string GetWindowTitleFormat() const { return windowTitleFormat; }
	inline float GetCurrentFps() const { return currentFps; }
	inline float GetAverageFps() const { return averageFps; }
	inline float GetDeltaTime() const { return deltaTime; }
	inline float GetTargetFps() const { return maxFps; }
	inline float GetWindowTitleUpdatePeriod() const { return windowTitleUpdatePeriod; }

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