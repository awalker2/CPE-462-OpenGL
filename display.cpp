#include "display.h"
#include<GLEW\glew.h>
#include<iostream>

using namespace std;

display::display(int width, int height, int bits,const string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//Set the minimum amount of bits desired for colors and set double buffering
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, bits);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, bits);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, bits);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, bits);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, bits*4);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//Create the window
	_window = SDL_CreateWindow(title.c_str(), 1, 31, width, height, SDL_WINDOW_OPENGL);
	_glContext = SDL_GL_CreateContext(_window);
	//Check if Glew can be initialized
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		cerr << "Could not initialze Glew" << endl;
	}
	//Code to allow depth testing
	glEnable(GL_DEPTH_TEST);
	//Set closed boolean, store width and height
	isClosed = false;
	aspect = float(width) / float(height);


}

void display::tellPosition(camera &camera)
{
	system("cls");
	cout << "Camera Position: ( " << camera.position.x << " ," << camera.position.y << " ," << camera.position.z << " )" << endl;
	cout << "Camera Forward Vector: ( " << camera.forward.x << " ," << camera.forward.y << " ," << camera.forward.z << " )" << endl;
}

void display::swapBuffers(camera &camera)
{
	//Keep window open as long as it is not closed
	SDL_GL_SwapWindow(_window);

	SDL_Event event;
	float increment = 0.1;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isClosed = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			//For looking around
			case SDLK_LEFT: camera.forward.x = camera.forward.x + increment; tellPosition(camera); break;
			case SDLK_RIGHT: camera.forward.x = camera.forward.x - increment; tellPosition(camera); break;
			case SDLK_UP: camera.forward.y = camera.forward.y + increment; tellPosition(camera); break;
			case SDLK_DOWN: camera.forward.y = camera.forward.y - increment; tellPosition(camera); break;
			//For moving
			case SDLK_a: camera.position.x = camera.position.x + increment; tellPosition(camera); break;
			case SDLK_d: camera.position.x = camera.position.x - increment; tellPosition(camera); break;
			case SDLK_w: camera.position.z = camera.position.z + increment; tellPosition(camera); break;
			case SDLK_s: camera.position.z = camera.position.z - increment; tellPosition(camera); break;
			case SDLK_SPACE: camera.position.y = camera.position.y + increment; tellPosition(camera); break;
			case SDLK_c: camera.position.y = camera.position.y - increment; tellPosition(camera); break;
			//For setting vectors
			case SDLK_e: camera.forward = glm::vec3(0, 0, -1); tellPosition(camera); break;
			case SDLK_q: camera.forward = glm::vec3(0, 0, 1); tellPosition(camera); break;
			}
		}
	}
}

void display::prepDisplay()
{
	//Set the background color and reset bits, especially important to clear depth buffer for every render
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

display::~display()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
