#include "Camera.h"
Graphic::Graphic3D::Camera::Camera()
{
	_position = API::Data::Vec3(0.0f, 0.0f, 0.0f);
}
Graphic::Graphic3D::Camera::Camera(const API::Data::Vec3& position)
{
	_position = position;
}

void Graphic::Graphic3D::Camera::_rotate(API::Data::Vec3& angles)
{
	// Ograniczenie odchylenia gora/dol, zeby nie bylo ogladania swiata do gory nogami.
	if (angles.Y > 89.0f) angles.Y = 89.0f;
	if (angles.Y < -89.0f) angles.Y = -89.0f;
	angles.Z = 0.0f; // Nie pozwalamy na obrot w osi Z.
	// Aktualizacja wartosci.
	_xRotation += angles.X;
	_yRotation += angles.Y;
	// Obrocenie wektorow.
	_frontNormal.Rotate(angles);
	_rightNormal.Rotate(angles);
	_upNormal.Rotate(angles);
}

void Graphic::Graphic3D::Camera::_move(API::Data::Vec3& translation)
{
	_position.Translate(translation);
}

void Graphic::Graphic3D::Camera::_changeZoom(float deltaZoom)
{
	_zoom += deltaZoom;
	if (_zoom < 1.0f)
	{
		_zoom = 1.0f;
	}
	if (_zoom > 45.0f)
	{
		_zoom == 45.0f;
	}
}

void Graphic::Graphic3D::Camera::Move(Graphic::Graphic3D::CameraMovement direction, float deltaTime)
{
	float velocity = deltaTime * _movementSpeed;
	if (direction == Graphic::Graphic3D::CameraMovement::FORWARD)
	{
		_move(_frontNormal * velocity);
	}
	if (direction == Graphic::Graphic3D::CameraMovement::BACKWARD)
	{
		_move(-_frontNormal * velocity);
	}
	if (direction == Graphic::Graphic3D::CameraMovement::RIGHT)
	{
		_move(_rightNormal * velocity);
	}
	if (direction == Graphic::Graphic3D::CameraMovement::LEFT)
	{
		_move(-_rightNormal * velocity);
	}
}

void Graphic::Graphic3D::Camera::Rotate(float x, float y)
{
	API::Data::Vec3 vec = API::Data::Vec3(x * _mouseSensitivity, y * _mouseSensitivity, 0.0f);
	_rotate(vec);
}

void Graphic::Graphic3D::Camera::Zoom(float deltaZoom)
{
	_changeZoom(deltaZoom);
}

float Graphic::Graphic3D::Camera::GetZoom() const
{
	return _zoom;
}

API::Data::Vec3 Graphic::Graphic3D::Camera::GetPosition() const
{
	return _position;
}

API::Data::Mat4* Graphic::Graphic3D::Camera::GetViewMatrix()
{
	glm::vec3 position = glm::vec3(_position.X, _position.Y, _position.Z);
	glm::vec3 front = glm::vec3(_frontNormal.X, _frontNormal.Y, _frontNormal.Z);
	glm::vec3 up = glm::vec3(_upNormal.X, _upNormal.Y, _upNormal.Z);
	glm::mat4 view = glm::lookAt(position, position + front, up);
	API::Data::Mat4* result = new API::Data::Mat4();
	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result->SetValue(i, j, view[i][j]);
		}
	}
	return result;
}

API::Data::Mat4 Graphic::Graphic3D::Camera::GetProjectionMatrix(float screenWidth, float screenHeight) const
{
	glm::mat4 projection = glm::perspective(glm::radians(_zoom), screenWidth/screenHeight, 0.1f, 100.0f);
	API::Data::Mat4 result = API::Data::Mat4();
	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.SetValue(i, j, projection[i][j]);
		}
	}
	return result;
}