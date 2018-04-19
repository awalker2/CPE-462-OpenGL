#include "shader.h"
#include<fstream>
#include<iostream>

void shader::bind()
{
	glUseProgram(_program);
}

void shader::update(const transform& transform, const camera& camera)
{
	//Calculate new matrix, need to transpose manually created matrices
	glm::mat4 model = camera.getViewProjection() * glm::transpose(transform.getModel());
	//Call update to transform matrix and draw mesh with new vertex locations 
	glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static void checkShaderError(GLuint shader, GLuint flag, bool program, const string& errMsg)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	//Need to know if it is a program or not and get errors from GL for troubleshooting
	if (program)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}
	if (success == GL_FALSE)
	{
		if (program)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		//Return the error message if needed
		cerr << errMsg << ": '" << error << " ' " << endl;
	}
}

static GLuint createShader(const string& text, GLenum shaderType)
{
	//Take the text of the shader as input and create it
	GLuint shader = glCreateShader(shaderType);
	//GLuint will be 0 if error creating
	if (shader == 0)
	{
		cerr << "Error creating shader" << endl;
	}
	//Can now attempt to compile shader
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringsLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringsLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);
	glCompileShader(shader);
	//Check if there was an error compiling shader
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed: ");

	return shader;
}

//Wrote our own version of this function
static string loadShader(const string& inputFile)
{
	ifstream readFile;
	string output;
	string inLine;
	readFile.open(inputFile.c_str());

	if (!readFile) 
	{
		cerr << "Error opening file: " << inputFile << endl;
		return NULL;
	}
	while (readFile.good())
	{
		getline(readFile, inLine);
		output.append(inLine + "\n");
	}
	return output;
}

shader::shader(const string& file)
{
	//Create the fragment and vertex shaders baded on extensions
	_program = glCreateProgram();
	_shaders[0] = createShader(loadShader(file+".vertex"), GL_VERTEX_SHADER);
	_shaders[1] = createShader(loadShader(file+".frag"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < _numShaders; i++)
	{
		glAttachShader(_program, _shaders[i]);
	}
	//Bind the attributes from the shaders
	glBindAttribLocation(_program, 0, "position");
	glBindAttribLocation(_program, 1, "texCoord");
	//See if both the shader link and actual program are valid
	glLinkProgram(_program);
	checkShaderError(_program, GL_LINK_STATUS, true, "Error linking shader: ");
	glValidateProgram(_program);
	checkShaderError(_program, GL_VALIDATE_STATUS, true, "Program not valid: ");

	//Access to transform uniform
	_uniforms[TRANSFORM_U] = glGetUniformLocation(_program, "transform");
}


shader::~shader()
{
	for (int i = 0; i < _numShaders; i++)
	{
		glDetachShader(_program, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}
	glDeleteProgram(_program);
}

