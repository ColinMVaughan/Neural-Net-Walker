//Brent Cowan Jan. 2015

#ifndef _Keyboard_
#define _Keyboard_

class Keyboard
{
private:
	

	bool key[sf::Keyboard::KeyCount];
	bool previous[sf::Keyboard::KeyCount];
	unsigned char unicode[sf::Keyboard::KeyCount];
	unsigned char unicodeShift[sf::Keyboard::KeyCount];

public:
	Keyboard();
	void Begin();
	void SetDown(short keyCode);
	void SetUp(short keyCode);
	bool GetHold(short keyCode);
	bool GetPress(short keyCode);
	bool GetRelease(short keyCode);
	unsigned char ConvertToUnicode(short keyCode, bool shift);
};

#endif