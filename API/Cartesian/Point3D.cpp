#include "Point3D.h"
API::Cartesian::Point3D::Point3D() : Object3D()
{
}
API::Cartesian::Point3D::Point3D(float x, float y, float z) : Object3D(x, y, z)
{
}

API::Cartesian::Point3D::Point3D(API::Data::Vec3& vec) : Object3D(vec.X, vec.Y, vec.Z)
{
}

void API::Cartesian::Point3D::Move(API::Data::Vec3& vector)
{
	SetCoords3D(this->_x + vector.X, this->_y + vector.Y, this->_z + vector.Z);
}
void API::Cartesian::Point3D::Move(API::Data::Vec3* vector)
{
	Move(*vector);
}
API::Cartesian::Point3D API::Cartesian::Point3D::GetMovedCopy(API::Data::Vec3& vector)
{
	return Point3D(this->_x + vector.X, this->_y + vector.Y, this->_z + vector.Z);
}

API::Cartesian::Point3D API::Cartesian::Point3D::GetMovedCopy(API::Data::Vec3* vector)
{
	return GetMovedCopy(*vector);
}

API::Cartesian::Point3D* API::Cartesian::Point3D::GetMovedCopyPtr(API::Data::Vec3& vector)
{
	return new Point3D(this->_x + vector.X, this->_y + vector.Y, this->_z + vector.Z);
}

API::Cartesian::Point3D* API::Cartesian::Point3D::GetMovedCopyPtr(API::Data::Vec3* vector)
{
	return GetMovedCopyPtr(*vector);
}

API::Data::Vec3 API::Cartesian::Point3D::ToVec3() const
{
	return API::Data::Vec3(_x, _y, _z);
}

API::Data::Vec3 API::Cartesian::Point3D::operator-(const API::Cartesian::Point3D& other)
{
	return API::Data::Vec3(_x - other.GetX(), _y - other.GetY(), _z - other.GetZ());
}