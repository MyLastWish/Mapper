#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Data/Vec3.h"
#include "Data/Mat4.h"
namespace Graphic
{
	namespace Graphic3D
	{
		enum class CameraMovement
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};
		class Camera
		{
		private:
			API::Data::Vec3 _position = API::Data::Vec3(0.0f, 0.0f, 0.0f);
			API::Data::Vec3 _frontNormal = API::Data::Vec3(0.0f, 0.0f, -1.0f);
			API::Data::Vec3 _upNormal = API::Data::Vec3(0.0f, 1.0f, 0.0f);
			API::Data::Vec3 _rightNormal = API::Data::Vec3(1.0f, 0.0f, 0.0f);
			API::Data::Vec3 _globalUpNormal = API::Data::Vec3(0.0f, 1.0f, 0.0f);
			float _xRotation = 0.0f;
			float _yRotation = 0.0f;

			// Parametry

			float _movementSpeed = 2.0f;
			float _mouseSensitivity = 0.1f;
			float _zoom = 45.0f;

			// Metody

			void _rotate(API::Data::Vec3&);
			void _move(API::Data::Vec3&);
			void _changeZoom(float);
		public:
			Camera();
			Camera(const API::Data::Vec3&);
			// Przemieszczanie kamery na podstawie kierunku i zmiany czasu.
			void Move(CameraMovement, float);
			void Rotate(float, float);
			void Zoom(float);
			float GetZoom() const;
			API::Data::Vec3 GetPosition() const;
			API::Data::Mat4 GetViewMatrix();
		};
	}
}
#endif