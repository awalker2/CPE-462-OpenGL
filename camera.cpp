#include "camera.h"

void camera::setUpVector(GLfloat x, GLfloat y, GLfloat z)
{
	_up.x = x;
	_up.y = y;
	_up.z = z;
}

void camera::setPosVector(GLfloat x, GLfloat y, GLfloat z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void camera::setForwardVector(GLfloat x, GLfloat y, GLfloat z)
{
	_forward.x = x;
	_forward.y = y;
	_forward.z = z;
}