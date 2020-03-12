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
void API::Data::Vec3::Rotate(const API::Data::Vec3 angles)
{
	Mat3 rotationMatrix = Mat3(0.0f);
	Mat3 xRotation = Mat3(0.0f);
	Mat3 yRotation = Mat3(0.0f);
	Mat3 zRotation = Mat3(0.0f);
	xRotation.SetValue(0, 0, std::cos(angles.X));
	xRotation.SetValue(0, 1, -std::sin(angles.X));
	xRotation.SetValue(1, 0, std::sin(angles.X));
	xRotation.SetValue(1, 1, std::cos(angles.X));
	xRotation.SetValue(2, 2, 1.0f);
	///
	yRotation.SetValue(0, 0, std::cos(angles.Y));
	yRotation.SetValue(0, 2, std::sin(angles.Y));
	yRotation.SetValue(1, 1, 1.0f);
	yRotation.SetValue(2, 0, -std::sin(angles.Y));
	yRotation.SetValue(2, 2, std::cos(angles.Y));
	///
	zRotation.SetValue(0, 0, 1.0f);
	zRotation.SetValue(1, 1, std::cos(angles.Z));
	zRotation.SetValue(1, 2, -std::sin(angles.Z));
	zRotation.SetValue(2, 1, std::sin(angles.Z));
	zRotation.SetValue(2, 2, std::cos(angles.Z));
}
void API::Data::Vec3::Translate(const API::Data::Vec3& vec)
{
	X = X + vec.X;
	Y = Y + vec.Y;
	Z = Z + vec.Z;
}

API::Data::Vec3 API::Data::Vec3::GetRotatedCopy(const API::Data::Vec3 angles)
{
	API::Data::Vec3 copy = API::Data::Vec3(this);
	copy.Rotate(angles);
	return copy;
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
float API::Data::Vec3::GetLength() const
{
	return std::sqrt(std::pow(X, 2) + std::pow(Y, 2) + std::pow(Z, 2));
}

API::Data::Vec3 API::Data::Vec3::AnglesFrom(const API::Data::Vec3& other)
{
	API::Data::Vec3 angles = API::Data::Vec3();
	angles.X = std::acos(DotProduct(API::Data::Vec3(0.0f, Y, Z), API::Data::Vec3(0.0f, other.Y, other.Z)) / (GetLength() * other.GetLength()));
	angles.Y = std::acos(DotProduct(API::Data::Vec3(X, 0.0f, Z), API::Data::Vec3(other.X, 0.0f, other.Z)) / (GetLength() * other.GetLength()));
	angles.Z = std::acos(DotProduct(API::Data::Vec3(X, Y, 0.0f), API::Data::Vec3(other.X, other.Y, 0.0f)) / (GetLength() * other.GetLength()));
	return angles;
}

bool API::Data::Vec3::operator==(const API::Data::Vec3& other)
{
	return X == other.X && Y == other.Y && Z == other.Z;
}

bool API::Data::Vec3::operator!=(const API::Data::Vec3& other)
{
	return X != other.X || Y != other.Y || Z != other.Z;
}

API::Data::Vec3& API::Data::Vec3::operator*(const float& factor)
{
	API::Data::Vec3 vec = API::Data::Vec3(X * factor, Y * factor, Z * factor);
	return vec;
}
API::Data::Vec3& API::Data::Vec3::operator=(const API::Data::Vec3& other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
	return *this;
}

API::Data::Vec3& API::Data::Vec3::operator-()
{
	API::Data::Vec3 vec = API::Data::Vec3(-X, -Y, -Z);
	return vec;
}API::Data::Vec3& API::Data::Vec3::operator-(const API::Data::Vec3& other)
{
	API::Data::Vec3 vec = API::Data::Vec3(X - other.X, Y - other.Y, Z - other.Z);
	return vec;
}
API::Data::Vec3& API::Data::Vec3::operator+(const API::Data::Vec3& other)
{
	API::Data::Vec3 vec = API::Data::Vec3(X + other.X, Y + other.Y, Z + other.Z);
	return vec;
}

float API::Data::DotProduct(const API::Data::Vec3& first, const API::Data::Vec3& second)
{
	return first.X * second.X + first.Y * second.Y;
}