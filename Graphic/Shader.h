#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
namespace Graphic
{
	class Shader
	{
	private:
		// the program ID
		unsigned int _ID;

		unsigned _calculateFileLength(const char*);
		bool _isShaderCorrect(GLuint, char*);
		bool _isProgramCorrect(char*);

	public:
		// constructor reads and builds the shader
		Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		// use/activate the shader
		void Use();
		// utility uniform functions
		void Set4f(const char* name, glm::vec4 value) const;
	};
}
#endif // !SHADER_H