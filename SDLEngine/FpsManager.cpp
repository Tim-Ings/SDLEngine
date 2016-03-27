#include "FpsManager.h"


FpsManager::FpsManager(int maxFrameRate) :
	targetFrameDuration(0.0f),
	maxFps(0.0f),
	currentFps(0.0f),
	frameCount(0),
	deltaTime(0.0f),
	windowTitleUpdatePeriod(-1),
	windowTitleFormat(""),
	window(nullptr),
	frameTimer(nullptr),
	windowTitleUpdateTimer(nullptr),
	titleBuffer(nullptr)
{
	maxFps = maxFrameRate;
	targetFrameDuration = (int)((1.0f / maxFps) * 1000.0f);
	titleBuffer = (char*)malloc(BUFSIZ);
	frameTimer.reset(new Timer());
	frameTimer->Start();
	windowTitleUpdateTimer.reset(new Timer());
	windowTitleUpdateTimer->Start();
}


FpsManager::~FpsManager()
{

}


void FpsManager::Update()
{
	// get ticks thsi frame andreset the timer
	int ticksThisFrame = frameTimer->GetTicks();
	frameTimer->Start();

	// are we running to quickly?
	if (maxFps != -1 && ticksThisFrame < targetFrameDuration)
	{
		// yes we have
		// sleep the current thread so we achieve our desired frame rate
		int sleepDuration = targetFrameDuration - ticksThisFrame;
		sleepDuration *= 2; // this makes it work correctly i think
		printf("too fast! sleeping for %dms\n", sleepDuration);
		SDL_Delay(sleepDuration);
	}

	// calculate fps
	currentFps = 1000.0f / (float)ticksThisFrame;
	averageFps = frameCount / (SDL_GetTicks() / 1000.f);
	if (averageFps > 2000000)
		averageFps = 0;

	// check if we need to update the window title
	if (windowTitleUpdatePeriod != -1 && window)
	{
		if (windowTitleUpdateTimer->GetTicks() > windowTitleUpdatePeriod)
		{
			printf("updating window title with cur fps=%f & avg fps=%f\n", currentFps, averageFps);
			sprintf_s(titleBuffer, BUFSIZ, windowTitleFormat.c_str(), currentFps, averageFps);
			SDL_SetWindowTitle(window, titleBuffer);
			windowTitleUpdateTimer->Start();
		}
	}


	// update delta time
	deltaTime = (float)(ticksThisFrame / 1000.0f);

	// keep track of total frames
	frameCount++; 

	
}