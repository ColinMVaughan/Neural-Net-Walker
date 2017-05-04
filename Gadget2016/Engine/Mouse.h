//Brent Cowan Jan. 2015

#ifndef _Mouse_
#define _Mouse_

class Mouse
{
private:
	sf::Mouse sfMouse;
	sf::Window* window;
	bool left, leftPrevious;
	bool right, rightPrevious;
	vec2 pos;

public:
	Mouse();
	void Init(sf::Window* window);
	void Update();
	bool GetLeftPress();
	bool GetLeftHold();
	bool GetLeftRelease();
	
	bool GetRightPress();
	bool GetRightHold();
	bool GetRightRelease();
	void Reset();
	vec2 GetPosition();
};

#endif