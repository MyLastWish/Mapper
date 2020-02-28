#include "Point2D.h"
API::Cartesian::Point2D::Point2D() : Object2D(0.0f, 0.0f)
{
}
API::Cartesian::Point2D::Point2D(float x, float y) : Object2D(x, y)
{
}
void API::Cartesian::Point2D::Move(API::Data::Vec2& vector)
{
	SetCoords2D(this->_x - vector.X, this->_y - vector.Y);
}