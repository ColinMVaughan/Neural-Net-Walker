//Brent Cowan 2016
class Camera2D
{
private:
	static mat4 projection;

	sf::Window* window;
	vec2 position;
	float rotation;
	float zoom;
	float aspectRatio;

public:
	Camera2D();
	void Init(sf::Window* window);
	void Activate();

	static mat4 GetProjection();
	
	vec2 GetPosition();
	void SetPosition(vec2 position);

	float GetRotation();
	void SetRotation(float rotation);

	float GetZoom();
	void SetZoom(float zoom);

	vec3 ScreenToCameraCoordinates(vec2 pos);
};