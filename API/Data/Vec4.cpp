#include "Vec4.h"

API::Data::Vec4::Vec4()
{
}

API::Data::Vec4::Vec4(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

API::Data::Vec4::Vec4(const API::Data::Vec4* original)
{
	this->X = original->X;
	this->Y = original->Y;
	this->Z = original->Z;
	this->W = original->W;
}

API::Data::Vec4::Vec4(const API::Data::Vec4& original)
{
	this->X = original.X;
	this->Y = original.Y;
	this->Z = original.Z;
	this->W = original.W;
}