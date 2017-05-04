//Brent Cowan 2016

class Sprite
{
private:
	mat4  matrix;
	vec3  position;
	vec2  scale;
	float rotation;
	vec2 minUV;
	vec2 maxUV;

	static bool    init;
	static GLuint  vertexArrayID;
	static GLuint  vertexBufferID;
	static GLuint  uvBufferID;
	static GLfloat vertexBuffer[12];
	static GLfloat uvBuffer[8];

public:
	Sprite();

	void Render();

	static void CleanUp();

	mat4 GetMatrix();

	vec3 GetPosition();
	void SetPosition(vec3 position);

	float GetRotation();
	void SetRotation(float rotation);

	vec2 GetScale();
	void SetScale(vec2 scale);

	vec4 GetUVs();
	void SetTextureCoords(float minU, float maxU, float minV, float maxV);
	void SetFrame(int frameWidth, int frameHeight, int imageWidth, int imageHeight, int frame, bool flipHorizontal);
};