#include "Color.h"
Graphic::Color::Color()
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 255;
}

Graphic::Color::Color(unsigned red, unsigned green, unsigned blue, unsigned alpha)
{
	Set(red, green, blue, alpha);
}

Graphic::Color::Color(float red, float green, float blue, float alpha)
{
	Set(_limit(red, 0.0f, 1.0f) * 255u, _limit(green, 0.0f, 1.0f) * 255u, _limit(blue, 0.0f, 1.0f) * 255u, _limit(alpha, 0.0f, 1.0f) * 255u);
}

Graphic::Color::Color(double red, double green, double blue, double alpha)
{
	Set(_limit(red, 0.0, 1.0) * 255u, _limit(green, 0.0, 1.0) * 255u, _limit(blue, 0.0, 1.0) * 255u, _limit(alpha, 0.0, 1.0) * 255u);
}

void Graphic::Color::Set(unsigned red, unsigned green, unsigned blue, unsigned alpha)
{
	_red = _limit(red, 0u, 255u);
	_green = _limit(green, 0u, 255u);
	_blue = _limit(blue, 0u, 255u);
	_alpha = _limit(alpha, 0u, 255u);
}

API::Data::Vec4 Graphic::Color::ToVec4()
{
	return API::Data::Vec4((float)_red / 255, (float)_green / 255, (float)_blue / 255, (float)_alpha / 255);
}