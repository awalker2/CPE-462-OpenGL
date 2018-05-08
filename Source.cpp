#include <iostream>
#include <GLEW\glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "model.c"
#include <SDL2\sdl.h>
using namespace std;

int main(int argc, char **argv)
{
	display display(1200, 720, 8, "OpenGLTest");

	vertex vertices[cubeVertices];
	for (int i = 0; i < cubeVertices; i++) {
		vertices[i] = vertex(glm::vec3(cubePositions[3 * i], cubePositions[3 * i + 1], cubePositions[3 * i + 2]), glm::vec2(cubeTexels[2 * i], cubeTexels[2 * i]));
	}

	/*Original test object of a pyramid
	vertex vertices[] = {	vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0, 0)),
							vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5, 1.0)),
							vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1, 0)),
							
							vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0, 0)),
							vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.5, 1.0)),
							vertex(glm::vec3(0.0f, -0.5f, -0.5f), glm::vec2(1, 0)),
							
							vertex(glm::vec3 (0.0f, 0.5f, 0.0f), glm::vec2(0, 0)),
							vertex(glm::vec3(0.0f, -0.5f, -0.5f), glm::vec2(0.5, 1.0)),
							vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1, 0)),
							
							vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0, 0)),
							vertex(glm::vec3(0.0f, -0.5f, -0.5f), glm::vec2(0.5, 1.0)),
							vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1, 0)), 
						};
	*/

	mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	shader shader("./res/basicShader");
	texture texture("./res/bricks.jpg");
	transform transform;
	camera camera(glm::vec3(0, 0, -3), 70.0f, display.aspect, 0.01f, 1000.0f);

	float counter = 0.0f;

	while (!display.isClosed)
	{	
		display.prepDisplay();

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//transform.translate(sinCounter, 0, 0);
		transform.rotY(counter);
		transform.rotX(counter);
		//transform.rotZ(counter);
		//transform.scale(counter, counter, counter);

		glm::mat4 temp = transform.getModel();

		shader.bind();
		texture.bind(0);
		shader.update(transform, camera);
		mesh.Draw();

		display.swapBuffers(camera);
		counter += 0.01f;
	}

	//system("pause");
	return 0;
}