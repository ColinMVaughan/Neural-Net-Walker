// Brent Cowan 2016
// Calculate FPS and elapsed time
// Also applies a smoothing algorithm to the time because most system count it in descrete
// portions or 20 to 40 ticks.

#ifndef _Timer_
#define _Timer_

class Timer
{
private:
	int lastTime;
	int thisTime;
	float smoothFPS;
	bool flag;
	float fps;
	float elapsedTime;
	float smoothElapsedTime;
	
public:
	void Init();
	void Update();

	float GetElapsedTime();
	int GetFramesPerSecond();
};

#endif