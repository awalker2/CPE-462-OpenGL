# CPE-462-OpenGL

This code is based of of the following youtube tutorial series by thebennybox:
https://www.youtube.com/watch?v=ftiKrP3gW3k&list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh
https://github.com/BennyQBD/ModernOpenGLTutorial

Libraries and Software Used:
public domain JPEG/PNG reader - http://nothings.org/stb_image.c
GLEW - http://glew.sourceforge.net/
SDL2 - https://www.libsdl.org/index.php
GLM - https://glm.g-truc.net/0.9.8/index.html
Blender Model Source - https://www.turbosquid.com/3d-models/3d-dragon-character-luxion-1205623

There were some slight changes to the display class from the tutorial to return an aspect ratio and deal with depth in a slightly different way, as well as user input being handled in Source.cpp to control the window size.

The mesh class was modified to send one list with offsets to the GPU instead of splitting the list.

The shader class and texture class stayed very similiar.

A lot of changes were made to the transform class to work more with the raw matrices. Since this was a final project for an image processing class, it was desired to show more work with the matrices instead of using library functions. As a side effect of this, the matrices must be transposed before being used by OpenGL since the library functions would normally transpose for you.

The camera class was updated with manual calculation of the perspective matrix, but still used a library function for the lookAt matrix (attempt was made, but the library function handled farther distances much better without distortion).

Charles Bethin, my partner for this group project, assisted me in adding keyboard user input to the display class to move the camera and he also found a Blender Model online (model.c is the export) that he was able to load in Source.cpp.

How to run the code - This repository was made using Visual Studio 2013 and includes all the files in the project folder (directory below the one containing the solution file). An empty project can be made with this in it, but needs glew32.dll, SDL2.dll, and the res folder need to be copied in the Debug or Release folder (the one in the same directory as the solution file).


