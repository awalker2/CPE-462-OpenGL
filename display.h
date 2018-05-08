#pragma once

#include<SDL2\SDL.h>
#include<string>
#include "camera.h"

using namespace std;

class display
{
public:
	display(int width, int height, int bits, const string& title);
	void swapBuffers(camera &camera);
	void tellPosition(camera &camera);
	void prepDisplay();
	bool isClosed;
	virtual ~display();
	float aspect;
private:
	SDL_Window* _window;
	SDL_GLContext _glContext;
};


