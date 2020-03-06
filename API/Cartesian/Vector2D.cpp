#include "Vector2D.h"
API::Cartesian::Vector2D::Vector2D() : Object2D(0.0f, 0.0f)
{
}
API::Cartesian::Vector2D::Vector2D(const Vector2D& original) : Object2D(0.0f, 0.0f)
{
	SetPoints(original.GetStart(), original.GetEnd());
}
API::Cartesian::Vector2D::Vector2D(float x, float y) : Object2D(x, y)
{
	SetCoords2D(x, y);
}
API::Cartesian::Vector2D::Vector2D(API::Cartesian::Point2D start, API::Cartesian::Point2D end) : Object2D(0.0f, 0.0f)
{
	_start = start; _end = end;
}
float API::Cartesian::Vector2D::GetX() const
{
	return _end.GetX() - _start.GetX();
}
float API::Cartesian::Vector2D::GetY() const
{
	return _end.GetY() - _start.GetY();
}
float API::Cartesian::Vector2D::GetLength() const
{
	return std::sqrt(std::pow(this->_x, 2) + std::pow(this->_y, 2));
}
API::Cartesian::Point2D API::Cartesian::Vector2D::GetStart() const
{
	return _start;
}
API::Cartesian::Point2D API::Cartesian::Vector2D::GetEnd() const
{
	return _end;
}
void API::Cartesian::Vector2D::MoveStart(API::Data::Vec2 vec)
{
	_start.Move(vec);
}
void API::Cartesian::Vector2D::MoveEnd(API::Data::Vec2 vec)
{
	_end.Move(vec);
}
void API::Cartesian::Vector2D::SetPoints(API::Cartesian::Point2D start, API::Cartesian::Point2D end)
{
	_start = start;
	_end = end;
}
//API::Cartesian::Vector2D* API::Cartesian::Vector2D::GetPerpendicularCopy(Direction dir)
//{
//	API::Cartesian::Vector2D* copy = this;
//	API::Cartesian::Vector2D* crossResult;
//	API::Cartesian::Vector2D* planarVector = new API::Cartesian::Vector2D(0.0f, 0.0f);
//	if (dir == Direction::RIGHT)
//	{
//		planarVector->Invert();
//	}
//	//crossResult = _crossProduct(copy, planarVector);
//	return crossResult; // TODO: Dokonczyc metode!
//}
API::Cartesian::Vector2D API::Cartesian::Vector2D::GetMultipliedCopy(float factor)
{
	API::Cartesian::Vector2D copy = API::Cartesian::Vector2D((*this));
	copy.MoveEnd(API::Data::Vec2(copy.GetX() * (1.0f - factor), copy.GetY() * (1.0f - factor)));
	return copy;
}
void API::Cartesian::Vector2D::Invert()
{
	SetPoints(_end, _start);
}
API::Cartesian::Vector2D& API::Cartesian::Vector2D::operator=(const Vector2D& original)
{
	this->SetPoints(original.GetStart(), original.GetEnd());
	return *this;
}
float API::Cartesian::Vector2D::DotProduct(Vector2D& other)
{
	return GetX() * other.GetX() + GetY() * other.GetY();
}