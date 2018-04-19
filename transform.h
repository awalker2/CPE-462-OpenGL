#pragma once

#include<GLM\glm\glm.hpp>
#include<GLM\glm\gtx\transform.hpp>
#include <GLEW\glew.h>

//transform reference - https://open.gl/transformations

//This was the tutorial implementation of the transform class, but used vectors that then got translated to matrices
/*
class transform
{
public:
	transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
		_pos(pos),
		_rot(rot),
		_scale(scale) {}

	inline glm::mat4 getModel() const
	{
		//GLM has an easy way to convert vector into matrix
		glm::mat4 posMatrix = glm::translate(_pos);
		glm::mat4 scaleMatrix = glm::scale(_scale);
		//Rotation must be done separatly, able to interpolate bwtn rotations
		glm::mat4 rotXMatrix = glm::rotate(_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(_rot.z, glm::vec3(0, 0, 1));
		//Not communitative, need to multiply backwards, different effects deppending on order
		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;
		return posMatrix * rotMatrix *scaleMatrix;
	}

	inline glm::vec3& getPos() { return _pos; }
	inline glm::vec3& getRot() { return _rot; }
	inline glm::vec3& getScale() { return _scale; }
	
	inline void setPos(const glm::vec3& pos) { _pos = pos; }
	inline void setRot(const glm::vec3& rot) { _rot = rot; }
	inline void setScale(const glm::vec3& scale) { _scale = scale; }
private:
	glm::vec3 _pos;
	glm::vec3 _rot;
	glm::vec3 _scale;
};
*/


//This is our modified version that does not use vectors, and relies less on the libraries for matrix arithmetic
class transform
{
public:
	//Starting off all matrices with 1 on the diagnal so that they do nothing to the transform
	transform(glm::mat4& pos = glm::mat4(1.0f), glm::mat4& scale = glm::mat4(1.0f), glm::mat4& rotX = glm::mat4(1.0f), glm::mat4& rotY = glm::mat4(1.0f), glm::mat4& rotZ = glm::mat4(1.0f)) :
		_pos(pos),
		_scale(scale),
		_rotX(rotX),
		_rotY(rotY),
		_rotZ(rotZ) {}

	inline glm::mat4 getModel() const
	{
		//Can multiply three matrices together to get the result, reverse order as desired
		glm::mat4 rotMatrix = _rotX * _rotY * _rotZ;
		glm::mat4 finalMatrix = _pos * rotMatrix * _scale;
		return finalMatrix;
	}
	//Accessors to set the matrices correctly for the intended effects
	void translate(GLfloat x, GLfloat y, GLfloat z);
	void scale(GLfloat x, GLfloat y, GLfloat z);
	void rotX(GLfloat r);
	void rotY(GLfloat r);
	void rotZ(GLfloat r);

private:
	glm::mat4& _pos;
	glm::mat4& _scale;
	glm::mat4& _rotX;
	glm::mat4& _rotY;
	glm::mat4& _rotZ;
};
