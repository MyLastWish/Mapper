#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "Object2D.h"
namespace API
{
	namespace Cartesian
	{
		class Object3D : public Object2D
		{
		protected:
			float _z;
		public:
			Object3D();
			Object3D(float x, float y, float z);
			virtual float GetZ() const;
			void SetCoords3D(float x, float y, float z);
			std::vector<float> GetCoordsInArray() override;
		};
	}
}

#endif