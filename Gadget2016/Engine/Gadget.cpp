//Brent Cowan 2016

#include "Engine.h"

Gadget::Gadget()
{
	color = vec3(0.0f, 0.0f, 0.0f);
}

Gadget::~Gadget()
{
	Sprite::CleanUp();
}

void Gadget::OpenWindow(unsigned short width, unsigned short height, bool fullScreen, bool resize, bool titleBar)
{
	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	// Create the main window
	sf::Uint32 windowStyle = sf::Style::Default;
	if (!resize)
	{
		if (windowStyle & sf::Style::Resize) { windowStyle -= sf::Style::Resize; }
	}

	if (!titleBar)
	{
		if (windowStyle & sf::Style::Close) { windowStyle -= sf::Style::Close; }
		if (windowStyle & sf::Style::Titlebar) { windowStyle -= sf::Style::Titlebar; }
	}

	if (fullScreen) { windowStyle = windowStyle | sf::Style::Fullscreen; }
	window.create(sf::VideoMode(width, height), "Gadget", windowStyle, contextSettings);
	
	window.setVerticalSyncEnabled(true);

	// Make it the active window for OpenGL calls
	window.setActive();
	
	glewInit();
	mouse.Init(&window);
	camera.Init(&window);
	timer.Init();

	// Set the clear color
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Disable lighting and texturing
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, window.getSize().x, window.getSize().y);
}

bool Gadget::Update()
{
	if (!window.isOpen()) { return false; }

	window.display();

	keyboard.Begin();

	// Process events
	sf::Event event;
	while (window.pollEvent(event))
	{
		// Close window: exit
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			keyboard.SetDown(event.key.code);
		}

		if (event.type == sf::Event::KeyReleased)
		{
			keyboard.SetUp(event.key.code);
		}

		// Escape key: exit
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			window.close();

		// Resize event: adjust the viewport
		if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
			//cam.SetAspectRatio(float(event.size.width) / float(event.size.height));
		}
	}

	
	mouse.Update();

	timer.Update();

	glClearColor(color.r, color.g, color.b, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.Activate();

	return true;
}

void Gadget::SetBackgroundColor(float red, float green, float blue)
{
	color.r = red; color.g = green; color.b = blue;
}