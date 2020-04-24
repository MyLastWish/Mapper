#include "Shader.h"
#include <iostream>
Graphic::Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	std::fstream vertexFile;
	std::fstream fragmentFile;
	vertexFile.exceptions(std::fstream::badbit | std::fstream::failbit);
	fragmentFile.exceptions(std::fstream::badbit | std::fstream::failbit);
	unsigned vertexLength = _calculateFileLength(vertexShaderPath);
	unsigned fragmentLength = _calculateFileLength(fragmentShaderPath);
	char* vertexStream = (char*)malloc(vertexLength);
	char* fragmentStream = (char*)malloc(fragmentLength);
	std::string vertexString, fragmentString;
	try
	{
		std::stringstream vertexSS, fragmentSS;
		vertexFile.open(vertexShaderPath);
		vertexSS << vertexFile.rdbuf();
		vertexFile.close();
		fragmentFile.open(fragmentShaderPath);
		fragmentSS << fragmentFile.rdbuf();
		fragmentFile.close();
		vertexString = vertexSS.str();
		fragmentString = fragmentSS.str();
	}
	catch (std::fstream::failure)
	{
		printf("\nShader file loading error.\n");
	}
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	char log[512];
	if (_isShaderCorrect(vertexShader, log))
	{
		printf(log);
	}
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	if (_isShaderCorrect(fragmentShader, log))
	{
		printf(log);
	}
	_ID = glCreateProgram();
	glAttachShader(_ID, vertexShader);
	glAttachShader(_ID, fragmentShader);
	glLinkProgram(_ID);
	if (_isProgramCorrect(log))
	{
		printf(log);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned Graphic::Shader::_calculateFileLength(const char* fileName)
{
	FILE* file;
	file = fopen(fileName, "r");
	if (file == NULL)
	{
		return 0;
	}
	fseek(file, 0, SEEK_END);
	unsigned length = ftell(file);
	fclose(file);
	return length;
}

void Graphic::Shader::Use()
{
	glUseProgram(_ID);
}

bool Graphic::Shader::_isShaderCorrect(GLuint shaderID, char* log)
{
	int success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, log);
		return false;
	}
	return true;
}

bool Graphic::Shader::_isProgramCorrect(char* log)
{
	int success = 0;
	glGetProgramiv(_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_ID, 512, NULL, log);
		return false;
	}
	return true;
}

void Graphic::Shader::Set4f(const char* name, const API::Data::Vec4& value) const
{
	glUniform4f(glGetUniformLocation(_ID, name), value.X, value.Y, value.Z, value.W);
	std::cout << name << " set to " << std::endl;
}

void Graphic::Shader::SetMatrix4f(const char* name, const API::Data::Mat4& value) const
{
	std::cout << name << std::endl;
	std::cout << "------------" << std::endl;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			std::cout << "[" << value[j][i] << "]\t\t";
		}
		std::cout << std::endl;
	}
	glUniformMatrix4fv(glGetUniformLocation(_ID, name), 1, false, value.GetMatrixPointer());
}