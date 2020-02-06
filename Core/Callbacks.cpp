#include "Callbacks.h"

void Callbacks::ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void Callbacks::MouseCallback(GLFWwindow* window, double x, double y)
{
}