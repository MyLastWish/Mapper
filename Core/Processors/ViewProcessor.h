#ifndef VIEW_PROCESSOR_H
#define VIEW_PROCESSOR_H
#include <GLFW/glfw3.h>
#include "3D/Camera.h"
#include "2D/Cursor.h"
namespace Processors
{
	class ViewProcessor // TOOD: Do zmiany, za duzo odpowiedzialnosci na jendej klasie.
	{
	private:
		GLFWwindow* _window = nullptr;
		Graphic::Graphic3D::Camera* _camera = nullptr;
		Graphic::Graphic2D::Cursor* _cursor = nullptr;
		float _deltaTime = 0;
		long float _lastTime = 0;
		bool _isKeyPressed(int);
		void _updateTime();
	public:
		ViewProcessor();
		ViewProcessor(Graphic::Graphic3D::Camera*);
		ViewProcessor(Graphic::Graphic3D::Camera*, Graphic::Graphic2D::Cursor*);
		ViewProcessor(Graphic::Graphic3D::Camera*, Graphic::Graphic2D::Cursor*, GLFWwindow*);
		ViewProcessor(Graphic::Graphic3D::Camera*, GLFWwindow*);
		void ProcessKeyboardInput();
		void ProcessAll();
		void MouseCallback(GLFWwindow*, double, double);
	};
}
#endif // !VIEW_PROCESSOR_H
