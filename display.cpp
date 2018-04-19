#include "display.h"
#include<GLEW\glew.h>
#include<iostream>

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
	_window = SDL_CreateWindow(title.c_str(), 50, 50, width, height, SDL_WINDOW_OPENGL);
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

void display::swapBuffers()
{
	//Keep window open as long as it is not closed
	SDL_GL_SwapWindow(_window);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isClosed = true;
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
