#ifndef VIEW_PROCESSOR_H
#define VIEW_PROCESSOR_H
#include "3D/Camera.h"
#include <GLFW/glfw3.h>
#include "2D/Cursor.h"
#include "Scene.h"
namespace Processors
{
	class ViewProcessor // TOOD: Do zmiany, za duzo odpowiedzialnosci na jendej klasie.
	{
	private:
		GLFWwindow* _window = nullptr;
		Graphic::Graphic3D::Camera* _camera = nullptr;
		Graphic::Graphic2D::Cursor* _cursor = nullptr;
		Graphic::Graphic3D::Scene* _scene = nullptr;
		float _height = 0.0f;
		float _width = 0.0f;
		float _deltaTime = 0.0f;
		float _lastTime = 0.0f;
		bool _isKeyPressed(int);
		void _updateTime();
	public:
		ViewProcessor();
		ViewProcessor(Graphic::Graphic3D::Camera*);
		ViewProcessor(Graphic::Graphic3D::Camera*, Graphic::Graphic2D::Cursor*);
		ViewProcessor(Graphic::Graphic3D::Camera*, Graphic::Graphic2D::Cursor*, GLFWwindow*);
		ViewProcessor(Graphic::Graphic3D::Camera*, GLFWwindow*);
		void SetSize(float, float);
		void SetScene(Graphic::Graphic3D::Scene*);
		void ProcessKeyboardInput();
		void ProcessAll();
		void MouseCallback(GLFWwindow*, double, double);
		void UpdateMatrices();
	};
}
#endif // !VIEW_PROCESSOR_H
