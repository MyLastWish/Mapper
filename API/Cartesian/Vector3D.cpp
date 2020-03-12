#include "Vector3D.h"
API::Cartesian::Vector3D::Vector3D()
{
	SetPoints(Point3D(), Point3D());
}
API::Cartesian::Vector3D::Vector3D(Point3D start, Point3D end)
{
	SetPoints(start, end);
}
API::Cartesian::Vector3D::Vector3D(API::Cartesian::Point3D start, API::Data::Vec3 vec)
{
	SetPoints(start, API::Cartesian::Point3D(start.GetX() + vec.X, start.GetY() + vec.Y, start.GetZ() + vec.Z));
}

float API::Cartesian::Vector3D::GetX() const
{
	return _end.GetX() - _start.GetX();
}
float API::Cartesian::Vector3D::GetY() const
{
	return _end.GetY() - _start.GetY();
}
float API::Cartesian::Vector3D::GetZ() const
{
	return _end.GetZ() - _start.GetZ();
}
float API::Cartesian::Vector3D::GetLength() const
{
	return std::sqrt(std::pow(_end.GetX() - _start.GetX(), 2) + std::pow(_end.GetY() - _start.GetY(), 2) + std::pow(_end.GetZ() - _start.GetZ(), 2));
}
void API::Cartesian::Vector3D::SetPoints(Point3D start, Point3D end)
{
	_start = start;
	_end = end;
}
void API::Cartesian::Vector3D::MoveStart(API::Data::Vec3 vec)
{
	_start.Move(vec);
}
void API::Cartesian::Vector3D::MoveEnd(API::Data::Vec3 vec)
{
	_end.Move(vec);
}
void API::Cartesian::Vector3D::Move(API::Data::Vec3 vec)
{
	MoveStart(vec);
	MoveEnd(vec);
}
API::Cartesian::Point3D API::Cartesian::Vector3D::GetStart() const
{
	return _start;
}
API::Cartesian::Point3D API::Cartesian::Vector3D::GetEnd() const
{
	return _end;
}
API::Cartesian::Vector3D& API::Cartesian::Vector3D::operator=(const Vector3D& original)
{
	this->SetPoints(original.GetStart(), original.GetEnd());
	return *this;
}
//API::Cartesian::Vector3D* API::Cartesian::Vector3D::FindPerpendicular(Vector3D normal)
//{
//	float xThis = this->GetX();
//	float yThis = this->GetY();
//	float zThis = this->GetZ();
//	float xNormal = normal.GetX();
//	float yNormal = normal.GetY();
//	float zNormal = normal.GetZ();
//	return new Vector3D(
//		yThis * zNormal - yNormal * zThis,
//		xNormal * zThis - xThis * zNormal,
//		xThis * yNormal - xNormal * yThis);
//}
API::Cartesian::Vector3D* API::Cartesian::Vector3D::GetInvertedCopyPtr()
{
	return new Vector3D(_end, _start);
}
API::Cartesian::Vector3D API::Cartesian::Vector3D::GetInvertedCopy()
{
	return Vector3D(_end, _start);
}

API::Data::Vec3 API::Cartesian::Vector3D::GetVectorCoords() const
{
	return API::Data::Vec3(_end.GetX() - _start.GetX(), _end.GetY() - _start.GetY(), _end.GetZ() - _start.GetZ());
}