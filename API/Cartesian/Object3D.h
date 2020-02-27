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
			Object3D()
			{
				SetCoords3D((T)0.0f, (T)0.0f, (T)0.0f);
			}
			Object3D(T x, T y, T z)
			{
				SetCoords3D(x, y, z);
			}
			virtual T GetZ() const { return _z; }
			void SetCoords3D(T x, T y, T z)
			{
				this->_x = x;
				this->_y = y;
				this->_z = z;
			}
			std::vector<T> GetCoordsInArray() override
			{
				return std::vector<T> {this->_x, this->_y, this->_z};
			}
		};
	}
}

#endif