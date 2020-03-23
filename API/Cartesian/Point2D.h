#ifndef POINT2D_H
#define POINT2D_H
#include "Object2D.h"
#include "../Data/Vec2.h"
namespace API
{
	namespace Cartesian
	{
		class Point2D : public Object2D
		{
		public:
			Point2D();
			Point2D(float x, float y);
			void Move(API::Data::Vec2&);
			API::Data::Vec2& operator-(const Point2D&);
		};
	}
}
#endif // !POINT2D_H
