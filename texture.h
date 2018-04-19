#pragma once

#include<string>
#include <GLEW\glew.h>

using namespace std;

class texture
{
public:
	texture(const string& file);
	void bind(unsigned int unit);
	virtual ~texture();
private:
	GLuint _texture;
};

