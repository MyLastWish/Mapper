#include "Object2D.h"
API::Cartesian::Object2D::Object2D() {};
API::Cartesian::Object2D::Object2D(float x, float y)
{
	SetCoords2D(x, y);
}
void API::Cartesian::Object2D::SetCoords2D(float x, float y)
{
	_x = x;
	_y = y;
}
float API::Cartesian::Object2D::GetX() const
{
	return _x;
}
float API::Cartesian::Object2D::GetY() const
{
	return _y;
}
std::vector<float> API::Cartesian::Object2D::GetCoordsInArray()
{
	return std::vector<float> {_x, _y};
}

bool API::Cartesian::Object2D::operator!=(const Object2D& other)
{
	return _x != other.GetX() || _y != other.GetY();
}

bool API::Cartesian::Object2D::operator==(const Object2D& other)
{
	return _x == other.GetX() && _y == other.GetY();
}