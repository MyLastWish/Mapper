#include "ViewProcessor.h"
Processors::ViewProcessor::ViewProcessor()
{
}
Processors::ViewProcessor::ViewProcessor(Graphic::Graphic3D::Camera* cam)
{
	_camera = cam;
}

void Processors::ViewProcessor::ProcessAll()
{
	ProcessKeyboardInput();
}

Processors::ViewProcessor::ViewProcessor(Graphic::Graphic3D::Camera* cam, GLFWwindow* win)
{
	_camera = cam;
	_window = win;
}

Processors::ViewProcessor::ViewProcessor(Graphic::Graphic3D::Camera* cam, Graphic::Graphic2D::Cursor* cur)
{
	_camera = cam;
	_cursor = cur;
	//_cursor->SetCursorMovementReaction(_camera->Rotate);
}

Processors::ViewProcessor::ViewProcessor(Graphic::Graphic3D::Camera* cam, Graphic::Graphic2D::Cursor* cur, GLFWwindow* win)
{
	_camera = cam;
	_cursor = cur;
	_window = win;
	//_cursor->SetCursorMovementReaction(_camera->Rotate);
}

void Processors::ViewProcessor::ProcessKeyboardInput()
{
	_updateTime();
	if (_isKeyPressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(_window, true);
	}
	if (_isKeyPressed(GLFW_KEY_W))
	{
		_camera->Move(Graphic::Graphic3D::CameraMovement::FORWARD, _deltaTime);
	}
	if (_isKeyPressed(GLFW_KEY_S))
	{
		_camera->Move(Graphic::Graphic3D::CameraMovement::BACKWARD, _deltaTime);
	}
	if (_isKeyPressed(GLFW_KEY_A))
	{
		_camera->Move(Graphic::Graphic3D::CameraMovement::LEFT, _deltaTime);
	}
	if (_isKeyPressed(GLFW_KEY_D))
	{
		_camera->Move(Graphic::Graphic3D::CameraMovement::RIGHT, _deltaTime);
	}
}

bool Processors::ViewProcessor::_isKeyPressed(int key)
{
	return glfwGetKey(_window, key) == GLFW_PRESS;
}

void Processors::ViewProcessor::MouseCallback(GLFWwindow* window, double x, double y)
{
	if (window != _window)
	{
		return;
	}
	_cursor->UpdateAndReact(x, y);
}

void Processors::ViewProcessor::_updateTime()
{
	float currentTime = glfwGetTime();
	_deltaTime = currentTime - _lastTime;
	_lastTime = currentTime;
}

void Processors::ViewProcessor::SetSize(float h, float w)
{
	_height = h;
	_width = w;
}

void Processors::ViewProcessor::UpdateMatrices()
{
	_camera->UpdateView(_scene->GetShaderPtr());
	_camera->UpdateProjection(_scene->GetShaderPtr(), _width, _height);
}

void Processors::ViewProcessor::SetScene(Graphic::Graphic3D::Scene* scene)
{
	if(scene == nullptr)
	{
		return;
	}
	_scene = scene;
}