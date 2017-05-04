//Brent Cowan 2016
//The shader loader comes from: http://www.opengl-tutorial.org/

#ifndef _SHADER_
#define _SHADER_

class Shader
{
private:
	bool init;
	GLuint ID;

public:
	Shader();
	~Shader();

	bool Load(const char * vertex_file_path, const char * fragment_file_path);
	void Activate();
	void SetImage(GLuint imageID, char* name, int imageNum);
	void SetFloat(char* name, float value);
	void SetVec4(char* name, vec4 vec);
	void SetVec4(char* name, float x, float y, float z, float w);
	void SetMat4(char* name, mat4 matrix);

	static void Deactivate();
	static void Blend(int RenderMode);
};

#endif
