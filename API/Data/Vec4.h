#ifndef VEC4_H
#define VEC4_H
#include <assert.h>
namespace API
{
	namespace Data
	{
		struct Vec4
		{
		public:
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;
			float W = 0.0f;
			Vec4();
			Vec4(float, float, float, float);
			Vec4(const Vec4*);
			Vec4(const Vec4&);
			float& operator[](const int&);
			float operator[](const int&) const;
		};
	}
}
#endif