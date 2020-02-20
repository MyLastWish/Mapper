#ifndef POINT3D_H
#define POINT3D_H
#include "Vector3D.h"
namespace API
{
	namespace Cartesian
	{
		template <typename T> class API::Cartesian::Vector3D;
		template <typename T = float>
		class Point3D : public Object3D<T>
		{
		public:
			Point3D<T>(T x, T y, T z) : Object3D<T>(x, y, z)
			{
			}
			void Move(API::Cartesian::Vector3D<T>& vector)
			{
				SetCoords3D(this->_x - vector.GetX(), this->_y - vector.GetY(), this->_z - vector.GetZ());
			}
		};
	}
}
#endif