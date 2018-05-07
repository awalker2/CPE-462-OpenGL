#include "mesh.h"
#include <vector>

vertex::vertex(const glm::vec3& pos, const glm::vec2& texCoord)
{
	//Just refers to itself
	this->pos = pos;
	this->texCoord = texCoord;
}

mesh::mesh(vertex* vertices, unsigned int numVertices)
{
	//This method was given as part of Benny tutorial
	/*
	_drawCount = numVertices;
	
	glGenVertexArrays(1, &_vertexArrayObj);
	glBindVertexArray(_vertexArrayObj);

	vector<glm::vec3> positions;
	vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].getPos());
		texCoords.push_back(*vertices[i].getTexCoord());
	}
	
	glGenBuffers(N_BUFFS, _vertexArrayBuffs);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffs[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffs[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	*/

	//Alternate method, came up with it on our own based on tutorial, offsets instead of splits
	_drawCount = numVertices;
	//Send the data to the GPU
	glGenVertexArrays(1, &_vertexArrayObj);
	glBindVertexArray(_vertexArrayObj);
	
	glGenBuffers(N_BUFFS, _vertexArrayBuffs);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffs[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	//Tell the GPU the appropriate offset so every other entry is a vertex or texture point
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffs[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid*)(sizeof(glm::vec3)));

	glBindVertexArray(0);
}

mesh::~mesh()
{
	glDeleteVertexArrays(1, &_vertexArrayObj);
}

void mesh::Draw()
{
	glBindVertexArray(_vertexArrayObj);
	glDrawArrays(GL_TRIANGLES, 0, _drawCount);
	glBindVertexArray(0);
}
