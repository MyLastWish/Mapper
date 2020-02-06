#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "Object3D.h"
#include "Point3D.h"
#include <math.h>
namespace API
{
	namespace Cartesian
	{
		template <typename T = float>
		class Vector3D : public Object3D<T>
		{
		private:
			API::Cartesian::Point3D _start;
			API::Cartesian::Point3D _end;
		public:
			T GetLength() const
			{
				return std::sqrt(std::pow(_end.GetX() - _start.GetX(), 2), std::pow(_end.GetY() - _start.GetY(), 2), std::pow(_end.GetZ() - _start.GetZ(), 2));
			}
		};
	}
}
#endif