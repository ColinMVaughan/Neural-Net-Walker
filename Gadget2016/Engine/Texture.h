//Brent Cowan 2014

#ifndef _TEXTURE2D_
#define _TEXTURE2D_

class Texture
{
private:
	GLuint id;
	sf::Image image;
	bool init;
	unsigned short int width, height;

public:
	Texture();
	~Texture();
	bool Load(const char * file_name);
	bool Save(const char * file_name);
	void Create(unsigned short width, unsigned short height);
	void Update();
	void SetPixel(unsigned short x, unsigned short y, unsigned char red, 
		unsigned char green, unsigned char blue, unsigned char alpha);
	void GetPixel(unsigned short x, unsigned short y, unsigned char &red,
		unsigned char &green, unsigned char &blue, unsigned char &alpha);
	void ConvertToDistanceField();
	GLuint GetID();
	GLuint GetWidth();
	GLuint GetHeight();
};

#endif