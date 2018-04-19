#pragma once

#include<GLM\glm\glm.hpp>
#include<GLM\glm\gtx\transform.hpp>

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

};

