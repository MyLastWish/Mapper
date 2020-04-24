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

float& API::Data::Vec4::operator[](const int& index)
{
	assert(index >= 0 && index <= 3);
	if(index == 0) return this->X;
	if(index == 1) return this->Y;
	if(index == 2) return this->Z;
	if(index == 3) return this->W;
	return this->X;
}

float API::Data::Vec4::operator[](const int& index) const
{
	assert(index >= 0 && index <= 3);
	if(index == 0) return this->X;
	if(index == 1) return this->Y;
	if(index == 2) return this->Z;
	if(index == 3) return this->W;
	return this->X;
}
