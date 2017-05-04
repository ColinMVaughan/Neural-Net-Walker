// Brent Cowan 2016
// Calculate FPS and elapsed time

#include "Timer.h"
#include <windows.h>

void Timer::Init()
{
	flag = false; //set this to true after fist run
	smoothFPS = 60.0f;//stores frames per second
	lastTime = timeGetTime();//set last time to clock
	elapsedTime = 0.016f; //start off > 0 to prevent possible division by 0
	smoothElapsedTime = 0.016f;//smoothed version
}

void Timer::Update()
{
	thisTime = timeGetTime();//get time from clock

	//if this is the first run through,set lastTime to the current time
	if(!flag){flag = true; lastTime = thisTime;}

	//calculate the elapsed time
	elapsedTime = (float)(thisTime - lastTime)/1000.0f;
	
	lastTime = thisTime;

	//Now smooth the time
	smoothElapsedTime = (smoothElapsedTime*6.0f+elapsedTime)/7.0f;

	//Prevent low frame rates from causing collision errors
	if(smoothElapsedTime > 0.05f)smoothElapsedTime = 0.05f;

	//Calculate the frames per second
	fps = 1.0f / smoothElapsedTime;
	smoothFPS = (smoothFPS*199.0f + fps) / 200.0f;
}

float Timer::GetElapsedTime() { return smoothElapsedTime; }

int Timer::GetFramesPerSecond() { return int(smoothFPS+0.5f); }