#ifndef POINT2D_H
#define POINT2D_H
#include "Object2D.h"
#include "Vector2D.h"
namespace API
{
	namespace Cartesian
	{
		template <typename T> class Vector2D;
		template <typename T = float>
		class Point2D : public Object2D<T>
		{
		public:
			Point2D() : Object2D<T>((T)0.0f, (T)0.0f) {}
			Point2D(T x, T y) : Object2D<T>(x, y) {}
			void Move(API::Cartesian::Vector2D<T>& vector)
			{
				SetCoords2D(this->_x - vector.GetX(), this->_y - vector.GetY());
			}
		};
	}
}
#endif // !POINT2D_H
