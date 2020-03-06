#ifndef VEC3_H
#define VEC3_H
#include <math.h>
#include "Vec2.h"
namespace API
{
	namespace Data
	{
		struct Vec3
		{
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
			Vec3();
			Vec3(float, float, float);
			Vec3(Vec3*);
			// Zamienia zwrot wektora na przeciwny.
			void Invert();
			// Zwraca wskaznik na wektor o przeciwnym zwrocie.
			Vec3* GetInvertedCopyPtr();
			// Zwraca obiekt wektora o przeciwnym zwrocie.
			Vec3 GetInvertedCopy();
			float GetLength() const;
			API::Data::Vec3& operator=(const API::Data::Vec3&);
			bool operator==(const API::Data::Vec3&);
			bool operator!=(const API::Data::Vec3&);
		};
	}
}
#endif