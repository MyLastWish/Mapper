#include "Vec3.h"
API::Data::Vec3::Vec3()
{
}

API::Data::Vec3::Vec3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

API::Data::Vec3::Vec3(Vec3* original) : API::Data::Vec3::Vec3(original->X, original->Y, original->Z)
{
}

void API::Data::Vec3::Invert()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

API::Data::Vec3* API::Data::Vec3::GetInvertedCopyPtr()
{
	return new API::Data::Vec3(-X, -Y, -Z);
}

API::Data::Vec3 API::Data::Vec3::GetInvertedCopy()
{
	return API::Data::Vec3(-X, -Y, -Z);
}