//Brent Cowan 2014

#include "Engine.h"

//float Clamp(float num, float min, float max)
//{
//	if (num < min) return min;
//	if (num > max) return max;
//	return num;
//}

int Clamp(int num, int min, int max)
{
	if (num < min) return min;
	if (num > max) return max;
	return num;
}

Texture::Texture()
{
	init   = false;
	//keep   = false;
	width  = 0;
	height = 0;
}

Texture::~Texture()
{
	GLuint id = GetID();
	if(glIsTexture(id))
	{
		glDeleteTextures(1, &id);
	}
}

void Texture::Create(unsigned short width, unsigned short height)
{
	this->width  = width;
	this->height = height;

	image.create(width, height, sf::Color(0, 0, 0, 255));

	//Convert the SFML image to an OpenGL texture
	glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	init = true;
}

bool Texture::Load(const char * file_name)
{
	if(!image.loadFromFile(file_name))
	{
		//The image didn't load
		return false;
	}
	

	width  = image.getSize().x;
	height = image.getSize().y;

	//Convert the SFML image to an OpenGL texture
	glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	init = true;
	return true;
}

void Texture::Update()
{
	if (!init) { return; }

	//Convert the SFML image to an OpenGL texture
	glBindTexture(GL_TEXTURE_2D, id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
}

bool Texture::Save(const char * file_name)
{
	if(!init) {return false;}	
	return image.saveToFile(file_name);
}

void Texture::SetPixel(unsigned short x, unsigned short y, 
	unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	sf::Color tmpColor;
	tmpColor.r = red;
	tmpColor.g = green;
	tmpColor.b = blue;
	tmpColor.a = alpha;
	image.setPixel(x, y, tmpColor);
}

void Texture::GetPixel(unsigned short x, unsigned short y,
	unsigned char &red, unsigned char &green, unsigned char &blue, unsigned char &alpha)
{
	sf::Color tmpColor;
	tmpColor = image.getPixel(x, y);

	red   = tmpColor.r;
	green = tmpColor.g;
	blue  = tmpColor.b;
	alpha = tmpColor.a;
}

GLuint Texture::GetID()
{
	return id;
}

GLuint Texture::GetWidth()
{
	return width;
}

GLuint Texture::GetHeight()
{
	return height;
}

void Texture::ConvertToDistanceField()
{
	if (!init) { return; }

	unsigned short x, y;
	unsigned char r, g, b, a;
	float temp, center;

	//convert to floats
	std::vector<float> d;
	d.resize(width*height, 0.0f);

	//Copy from image
	for (x = 0; x < width; x++)
	{
		for (y = 0; y < height; y++)
		{
			GetPixel(x, y, r, g, b, a);
			d[x + y*width] = float(r) / 255.0f - 0.5f;
		}
	}

	//Calculate distance field
	for (int i = 0; i < width; i++)
	{
		for (x = 0; x < width; x++)
		{
			for (y = 0; y < height; y++)
			{
				center = d[x + y*width];
				if (center < -0.49f || center > 0.49f)//leave it alone if its an edge
				{
					//if outside look for the lowest distance
					if (center>0.0f)
					{
						//corners
						temp = d[Clamp(x - 1, 0, width - 1) + Clamp(y - 1, 0, height - 1)*width] + 1.414f;
						center = temp;

						temp = d[Clamp(x + 1, 0, width - 1) + Clamp(y - 1, 0, height - 1)*width] + 1.414f;
						if (temp < center) center = temp;

						temp = d[Clamp(x + 1, 0, width - 1) + Clamp(y + 1, 0, height - 1)*width] + 1.414f;
						if (temp < center) center = temp;

						temp = d[Clamp(x - 1, 0, width - 1) + Clamp(y + 1, 0, height - 1)*width] + 1.414f;
						if (temp < center) center = temp;

						//sides
						temp = d[Clamp(x - 1, 0, width - 1) + Clamp(y, 0, height - 1)*width] + 1.0f;
						if (temp < center) center = temp;

						temp = d[Clamp(x + 1, 0, width - 1) + Clamp(y, 0, height - 1)*width] + 1.0f;
						if (temp < center) center = temp;

						temp = d[Clamp(x, 0, width - 1) + Clamp(y - 1, 0, height - 1)*width] + 1.0f;
						if (temp < center) center = temp;

						temp = d[Clamp(x, 0, width - 1) + Clamp(y + 1, 0, height - 1)*width] + 1.0f;
						if (temp < center) center = temp;
					}
					else //look for the highest distance
					{
						//corners
						temp = d[Clamp(x - 1, 0, width - 1) + Clamp(y - 1, 0, height - 1)*width] - 1.414f;
						center = temp;

						temp = d[Clamp(x + 1, 0, width - 1) + Clamp(y - 1, 0, height - 1)*width] - 1.414f;
						if (temp > center) center = temp;

						temp = d[Clamp(x + 1, 0, width - 1) + Clamp(y + 1, 0, height - 1)*width] - 1.414f;
						if (temp > center) center = temp;

						temp = d[Clamp(x - 1, 0, width - 1) + Clamp(y + 1, 0, height - 1)*width] - 1.414f;
						if (temp > center) center = temp;

						//sides
						temp = d[Clamp(x - 1, 0, width - 1) + Clamp(y, 0, height - 1)*width] - 1.0f;
						if (temp > center) center = temp;

						temp = d[Clamp(x + 1, 0, width - 1) + Clamp(y, 0, height - 1)*width] - 1.0f;
						if (temp > center) center = temp;

						temp = d[Clamp(x, 0, width - 1) + Clamp(y - 1, 0, height - 1)*width] - 1.0f;
						if (temp > center) center = temp;

						temp = d[Clamp(x, 0, width - 1) + Clamp(y + 1, 0, height - 1)*width] - 1.0f;
						if (temp > center) center = temp;
					}
					d[x + y*width] = center;
				}
			}
		}
	}

	//Copy to image
	for (x = 0; x < width; x++)
	{
		for (y = 0; y < height; y++)
		{
			center = d[x + y*width];
			center = center / float(width);
			center += 0.5f;

			//Convert to byte
			temp = Clamp(center*3.0f-2.0f, 0.0f, 1.0f);
			temp = temp * 255.0f + 0.5f;
			if (temp >= 256.0f)temp = 255.1f;
			if (temp < 0.0f)temp = 0.00001f;
			r = unsigned char(temp);

			//Convert to byte
			temp = Clamp(center*3.0f-1.0f, 0.0f, 1.0f);
			temp = temp * 255.0f + 0.5f;
			if (temp >= 256.0f)temp = 255.1f;
			if (temp < 0.0f)temp = 0.00001f;
			g = unsigned char(temp);

			//Convert to byte
			temp = Clamp(center*3.0f, 0.0f, 1.0f);
			temp = temp * 255.0f + 0.5f;
			if (temp >= 256.0f)temp = 255.1f;
			if (temp < 0.0f)temp = 0.00001f;
			b = unsigned char(temp);

			SetPixel(x, y, r, g, b, 255);
		}
	}

	d.clear();
	
	//Send to video card
	glBindTexture(GL_TEXTURE_2D, id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
}