#include "Vec2.h"
API::Data::Vec2::Vec2()
{
}
API::Data::Vec2::Vec2(float x, float y)
{
	X = x;
	Y = y;
}

API::Data::Vec2::Vec2(Vec2* original) : API::Data::Vec2::Vec2(original->X, original->Y)
{
}

void API::Data::Vec2::Invert()
{
	X = -X;
	Y = -Y;
}

API::Data::Vec2* API::Data::Vec2::GetInvertedCopyPtr()
{
	return new API::Data::Vec2(-X, -Y);
}

API::Data::Vec2 API::Data::Vec2::GetInvertedCopy()
{
	return API::Data::Vec2(-X, -Y);
}