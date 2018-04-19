#pragma once

#include <string>
#include <GLEW\glew.h>
#include "transform.h"
#include "camera.h"

using namespace std;

class shader
{
public:
	shader(const string& file);
	void bind();
	void update(const transform& transform, const camera& camera);
	virtual ~shader();
private:
	static const unsigned int _numShaders = 2;
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};
	GLuint _program;
	GLuint _shaders[_numShaders];
	GLuint _uniforms[NUM_UNIFORMS];
};

