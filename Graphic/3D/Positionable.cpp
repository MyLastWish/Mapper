#include "Positionable.h"
#include <iostream>
Graphic::Graphic3D::Positionable::Positionable()
{
    SetPosition(API::Data::Vec3());
    SetRotation(API::Data::Vec3());
}

Graphic::Graphic3D::Positionable::Positionable(API::Data::Vec3 position, API::Data::Vec3 rotation)
{
    SetPosition(position);
    SetRotation(rotation);
}

void Graphic::Graphic3D::Positionable::SetRotation(API::Data::Vec3 rotation)
{
	rotation = rotation;
	_transformationChanged = true;
}

void Graphic::Graphic3D::Positionable::SetPosition(API::Data::Vec3 position)
{
	_position = position;
	_transformationChanged = true;
}

API::Data::Mat4 Graphic::Graphic3D::Positionable::GetTransformationMatrix() const
{
	std::cout << _position.X << "/" << _position.Y << "/" << _position.Z << std::endl;
	API::Data::Mat4 matrix = API::Data::Mat4();
	API::Data::Mat3 xRot = API::Data::Mat3();
	API::Data::Mat3 yRot = API::Data::Mat3();
	API::Data::Mat3 zRot = API::Data::Mat3();
	API::Data::Mat3 rotations = API::Data::Mat3();
	xRot.XRotation(_rotation.X);
	yRot.YRotation(_rotation.Y);
	zRot.ZRotation(_rotation.Z);
	rotations = xRot * yRot * zRot;
	matrix.MakeTranformationMatrix(rotations, _position);
	return matrix;
}

void Graphic::Graphic3D::Positionable::UpdateTransformation(Graphic::Shader* shader)
{
	if(!_transformationChanged)
	{
		return;
	}
	shader->SetMatrix4f("model", GetTransformationMatrix());
	_transformationChanged = false;
}