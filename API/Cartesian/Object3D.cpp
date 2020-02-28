#include "Object3D.h"
API::Cartesian::Object3D::Object3D()
{
	SetCoords3D(0.0f, 0.0f, 0.0f);
}
API::Cartesian::Object3D::Object3D(float x, float y, float z)
{
	SetCoords3D(x, y, z);
}
float API::Cartesian::Object3D::GetZ() const
{
	return _z;
}
std::vector<float> API::Cartesian::Object3D::GetCoordsInArray()
{
	return std::vector<float> {this->_x, this->_y, this->_z};
}
void API::Cartesian::Object3D::SetCoords3D(float x, float y, float z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}