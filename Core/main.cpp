#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Callbacks.h"
#include "Data/Image.h"
#include "Mesh.h"
int _glfwInitialize(GLFWwindow*& window)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(800, 600, "SvgMapper", NULL, NULL);
	if (window == NULL)
	{
		// Reakcja na niepowodzenie tworzenia okna.
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Ustawienie kontekstu okna jako obecnego.
	glfwMakeContextCurrent(window);
	//Processors::InputProcessor mainInputProcessor = Processors::InputProcessor(window);
	// Inicjalizacja GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// Reakcja na niepowodzenia inicjalizacji.
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	return 0;
}
int main()
{
	GLFWwindow* window;
	int initValue = _glfwInitialize(window);
	if (initValue != 0)
	{
		return initValue;
	}
	glfwSetFramebufferSizeCallback(window, Callbacks::ResizeCallback);
	//Processors::InputProcessor proc = Processors::InputProcessor(window);
	SVG::Data::Image* image = new SVG::Data::Image("D:\\Downloads\\rectangles.svg");
	Graphic::Shader* basicShader = new Graphic::Shader("C:\\Users\\Adam\\source\\repos\\MyLastWish\\SvgMapper\\SvgMapper\\basicShader.vert", "C:\\Users\\Adam\\source\\repos\\MyLastWish\\SvgMapper\\SvgMapper\\basicShader.frag");
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.1f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// proc.Process();
		//image->Draw(basicShader);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}