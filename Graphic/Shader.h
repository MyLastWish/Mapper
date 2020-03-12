#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Data/Mat4.h"
namespace Graphic
{
	class Shader
	{
	private:
		// Id programu
		unsigned int _ID;

		unsigned _calculateFileLength(const char*);

		// Metody sprawdzajace skompilowany shader.

		bool _isShaderCorrect(GLuint, char*);
		bool _isProgramCorrect(char*);

	public:
		// Konstruktor.
		Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
		// Aktywowanie programu shadera.
		void Use();

		// Ustawianie wartosci uniformow shadera.

		void Set4f(const char* name, const API::Data::Vec4& value) const;
		void SetMatrix4f(const char* name, const API::Data::Mat4& value) const;
	};
}
#endif // !SHADER_H