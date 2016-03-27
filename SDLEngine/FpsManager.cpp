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
	frameTimer = new Timer();
	frameTimer->Start();
	windowTitleUpdateTimer = new Timer();
	windowTitleUpdateTimer->Start();
}


FpsManager::~FpsManager()
{

}


void FpsManager::Update()
{
	// are we running to quickly?
	if (frameTimer->GetTicks() < targetFrameDuration)
	{
		// yes we have
		// sleep the current thread so we achieve our desired frame rate
		int sleepDuration = targetFrameDuration - frameTimer->GetTicks();
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
	}


	// check if we need to update the window title
	if (windowTitleUpdatePeriod != -1 && window)
	{
		if (windowTitleUpdateTimer->GetTicks() > windowTitleUpdatePeriod)
		{
			sprintf_s(titleBuffer, BUFSIZ, windowTitleFormat.c_str(), currentFps);
			SDL_SetWindowTitle(window, titleBuffer);
			windowTitleUpdateTimer->Start();
		}
	}


	// update delta time
	deltaTime = (float)(frameTimer->GetTicks() / 1000.0f);

	// keep track of total frames
	frameCount++; 

	// reset the timer
	frameTimer->Start();
}