#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "Object2D.h"
namespace API
{
	namespace Cartesian
	{
		template <typename T = float>
		class Object3D : public Object2D<T>
		{
		private:
			T _z;
		public:
			virtual T GetZ() const { return _z; }
			void SetCoords3D(T x, T y, T z)
			{
				_x = x;
				_y = y;
				_z = z;
			}
		};
	}
}

#endif