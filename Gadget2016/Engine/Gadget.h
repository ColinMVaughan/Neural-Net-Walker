//Brent Cowan 2016

class Gadget
{
private:
	vec3 color;

public:
	Gadget();
	~Gadget();
	void OpenWindow(unsigned short width, unsigned short height, bool fullScreen = false, bool resize = false, bool titleBar = true);
	void SetBackgroundColor(float red, float green, float blue);
	bool Update();

	Timer timer;
	Camera2D camera;
	Mouse mouse;
	Keyboard keyboard;
	sf::Window window;
};