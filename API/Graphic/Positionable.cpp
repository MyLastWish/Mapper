#include "Positionable.h"
API::Graphic::Positionable::Positionable()
{
    SetPosition(API::Data::Vec3());
    SetRotation(API::Data::Vec3());
}

API::Graphic::Positionable::Positionable(API::Data::Vec3 position, API::Data::Vec3 rotation)
{
    SetPosition(position);
    SetRotation(rotation);
}

void API::Graphic::Positionable::SetRotation(API::Data::Vec3 rotation)
{
	rotation = rotation;
}

void API::Graphic::Positionable::SetPosition(API::Data::Vec3 position)
{
	_position = position;
}

API::Data::Mat4 API::Graphic::Positionable::GetTransformationMatrix() const
{
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