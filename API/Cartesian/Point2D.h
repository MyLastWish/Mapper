#ifndef POINT2D_H
#define POINT2D_H
#include "Object2D.h"
namespace API
{
	namespace Cartesian
	{
		template <typename T = float>
		class Point2D : public Object2D<T>
		{
		public:
			Point2D();
			Point2D(T x, T y) : Object2D<T>(x, y) {}
			/*void Move(Vector2D<float>& vector)
			{
				SetCoords2D(_x - vector.GetX(), _y - vector.GetY());
			}*/
		};
	}
}
#endif // !POINT2D_H
