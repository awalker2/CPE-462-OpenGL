# CPE-462-OpenGL

This code is based of of the following youtube tutorial series by thebennybox:
https://www.youtube.com/watch?v=ftiKrP3gW3k&list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh
https://github.com/BennyQBD/ModernOpenGLTutorial

The image loader is from below:
public domain JPEG/PNG reader - http://nothings.org/stb_image.c

There were some slight changes to the display class from the tutorial to return an aspect ratio and deal with depth in a slightly different way.

The mesh class was modified to send one list with offsets to the GPU instead of splitting the list.

The shader class and texture class stayed very similiar.

A lot of changes were made to the transform class to work more with the raw matrices. Since this was a final project for an image processing class, it was desired to show more work with the matrices instead of using library functions. As a side effect of this, the matrices must be transposed before being used by OpenGL since the library functions would normally transpose for you.

The camera class is currently being updated to rely less on the library functions and manually calculate the matrix in my code.


