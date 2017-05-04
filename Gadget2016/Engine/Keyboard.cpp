//Brent Cowan Jan. 2015

#include "Engine.h"

Keyboard::Keyboard()
{
	for(int i = 0; i<sf::Keyboard::KeyCount; i++)
	{
		key[i] = false;
		previous[i] = false;
		unicode[i] = 0;
		unicodeShift[i] = 0;
	}

	//add unicode letters
	for (unsigned char i = sf::Keyboard::A; i<sf::Keyboard::Z+1; i++)
	{
		unicode[i] = i+97;
		unicodeShift[i] = i +65;
	}
	//add unicode numbers
	for (unsigned char i = sf::Keyboard::Num0; i<sf::Keyboard::Num9 + 1; i++)
	{
		unicode[i] = i + 22;
	}

	unicode[sf::Keyboard::Space] = 32;//SPACE

	unicodeShift[sf::Keyboard::Num1] = 33;//!
}

unsigned char Keyboard::ConvertToUnicode(short keyCode, bool shift)
{
	if (keyCode>100 || keyCode<0)
	{
		return 0;
	}
	else
	{
		if (shift) return unicodeShift[keyCode];
		else return unicode[keyCode];
	}
}

void Keyboard::Begin()
{
	for (int i = 0; i<sf::Keyboard::KeyCount; i++)
	{
		previous[i] = key[i];
	}
}

void Keyboard::SetDown(short keyCode)
{
	if(keyCode < sf::Keyboard::KeyCount)
	{
		key[keyCode] = true;
	}
}

void Keyboard::SetUp(short keyCode)
{
	if(keyCode < sf::Keyboard::KeyCount)
	{
		key[keyCode] = false;
	}
}

bool Keyboard::GetHold(short keyCode)
{
	if(keyCode < sf::Keyboard::KeyCount)
	{
		return key[keyCode];
	}
	else
	{
		return false;
	}
}

bool Keyboard::GetPress(short keyCode)
{
	if (keyCode < sf::Keyboard::KeyCount)
	{
		if (key[keyCode] && !previous[keyCode]){ return true; }
		else return false;
	}
	else
	{
		return false;
	}
}

bool Keyboard::GetRelease(short keyCode)
{
	if (keyCode < sf::Keyboard::KeyCount)
	{
		if (!key[keyCode] && previous[keyCode]){ return true; }
		else return false;
	}
	else
	{
		return false;
	}
}