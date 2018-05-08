#pragma once

#include<GLM\glm\glm.hpp>
#include<GLM\glm\gtx\transform.hpp>
#include <GLEW\glew.h>

//This was the tutorial version of the camera class
/*
class camera
{
public:
	camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		_perspective = glm::perspective(fov, aspect, zNear, zFar);
		_position = pos;
		_forward = glm::vec3(0, 0, 1);
		_up = glm::vec3(0, 1, 0);
	}

	inline glm::mat4 getViewProjection() const
	{
		return _perspective * glm::lookAt(_position, _position + _forward, _up);
	}

private:
	glm::mat4 _perspective;
	glm::vec3 _position;
	glm::vec3 _forward;
	glm::vec3 _up;

};*/

//This was our implementation of the camera class
//Projection matrix source: https://unspecified.wordpress.com/2012/06/21/calculating-the-gluperspective-matrix-and-other-opengl-matrix-maths/
class camera
{
public:
	camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		//Manual calculation of perspective matrix
		float f = 1 / tan(fov / 2);
		_perspective[0][0] = f/aspect;
		_perspective[1][1] = f;
		_perspective[2][2] = (zNear + zFar) / (zNear - zFar);
		_perspective[2][3] = (2 * zNear*zFar) / (zNear - zFar);
		_perspective[3][2] = -1;

		position = pos;
		forward = glm::vec3(0.0, 0.0, 1);
		up = glm::vec3(0.0, 1, 0.0);
	}

	inline glm::mat4 getViewProjection() const
	{
		return glm::transpose(_perspective) * glm::lookAt(position, position + forward, up);
	}
	//Ended up using public variables instead
	/*
	//Accessors to set the vectors to move the camera
	void setUpVector(GLfloat x, GLfloat y, GLfloat z);
	void setPosVector(GLfloat x, GLfloat y, GLfloat z);
	void setForwardVector(GLfloat x, GLfloat y, GLfloat z);
	//Getters to get the private variables
	glm::vec3 getUpVector();
	glm::vec3 getPosVector();
	glm::vec3 getForwardVector();
	*/
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
private:
	glm::mat4 _perspective = glm::mat4(0.0f);
	glm::mat4 _view = glm::mat4(0.0f);;
};

