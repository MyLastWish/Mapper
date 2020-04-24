#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <assert.h>
namespace API
{
	namespace Data
	{
		struct Mat3;
		struct Vec3
		{
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
			Vec3();
			Vec3(float, float, float);
			Vec3(Vec3*);
			void Translate(const Vec3&);
			void Rotate(const Vec3);
			Vec3 GetRotatedCopy(const Vec3);
			Vec3* GetRotatedCopyPtr(const Vec3);
			// Zamienia zwrot wektora na przeciwny.
			void Invert();
			// Zwraca wskaznik na wektor o przeciwnym zwrocie.
			Vec3* GetInvertedCopyPtr();
			// Zwraca obiekt wektora o przeciwnym zwrocie.
			Vec3 GetInvertedCopy();
			// Pozyskiwanie kata pomiedzy tym wektorem, a podanym jako argument, wyrazony w katach dla kazdej z osi.
			Vec3 AnglesFrom(const Vec3&);
			float GetLength() const;
			Vec3 operator*(const float&);
			Vec3& operator=(const API::Data::Vec3&);
			Vec3 operator-(const API::Data::Vec3&);
			Vec3 operator-();
			Vec3 operator+(const API::Data::Vec3&);
			bool operator==(const API::Data::Vec3&);
			bool operator!=(const API::Data::Vec3&);
			float& operator[](const int&);
			float operator[](const int&) const;
			friend float DotProduct(const Vec3&, const Vec3&);
		};
		float DotProduct(const Vec3&, const Vec3&);
	}
}
#endif