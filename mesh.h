#pragma once

#include<GLM\glm\glm.hpp>
#include<GLEW\glew.h>

using namespace std;

class vertex
{
public:
	vertex(const glm::vec3& pos, const glm::vec2&texCoord);

	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* getTexCoord() { return &texCoord; }
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class mesh
{
public:
	mesh(vertex* vertices, unsigned int numVertices);
	void Draw();
	virtual ~mesh();
private:
	enum
	{
		POS_VB,
		TEXCOORD_VB,
		N_BUFFS
	};
	GLuint _vertexArrayObj;
	GLuint _vertexArrayBuffs[N_BUFFS];
	unsigned int _drawCount;
};

