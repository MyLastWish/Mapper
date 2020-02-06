#ifndef POINT3D_H
#define POINT3D_H
namespace API
{
	namespace Cartesian
	{
		template <typename T = float>
		class Point3D : public Object3D<T>
		{
		public:
			void Move(Vector3D& vector)
			{
				SetCoords3D(_x - vector.GetX(), _y - vector.GetY(), _z - vector.GetZ());
			}
		};
	}
}
#endif