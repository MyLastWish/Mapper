#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <GLFW/glfw3.h>
namespace Callbacks
{
	void ResizeCallback(GLFWwindow* window, int width, int height);
	void MouseCallback(GLFWwindow* window, double x, double y);
}
#endif // !CALLBACKS_H