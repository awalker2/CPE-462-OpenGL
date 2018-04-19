#include "transform.h"

void transform::translate(GLfloat x, GLfloat y, GLfloat z)
{
	_pos[0][3] = x;
	_pos[1][3] = y;
	_pos[2][3] = z;
}

void transform::scale(GLfloat x, GLfloat y, GLfloat z)
{
	_scale[0][0] = x;
	_scale[1][1] = y;
	_scale[2][2] = z;
}

void transform::rotX(GLfloat r)
{
	_rotX[1][1] = cos(r);
	_rotX[1][2] = -sin(r);
	_rotX[2][1] = sin(r);
	_rotX[2][2] = cos(r);
}
void transform::rotY(GLfloat r){
	_rotY[0][0] = cos(r);
	_rotY[0][2] = sin(r);
	_rotY[2][0] = -sin(r);
	_rotY[2][2] = cos(r);
}

void transform::rotZ(GLfloat r){
	_rotZ[0][0] = cos(r);
	_rotZ[0][1] = -sin(r);
	_rotZ[1][0] = sin(r);
	_rotZ[1][1] = cos(r);
}



