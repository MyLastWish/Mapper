#ifndef POINT3D_H
#define POINT3D_H
#include "../Data/Vec3.h"
#include "Object3D.h"
namespace API
{
	namespace Cartesian
	{
		class Point3D : public Object3D
		{
		public:
			Point3D();
			Point3D(float x, float y, float z);
			Point3D(API::Data::Vec3&);
			void Move(API::Data::Vec3& vector);
			void Move(API::Data::Vec3* vector);
			Point3D GetMovedCopy(API::Data::Vec3& vector);
			Point3D GetMovedCopy(API::Data::Vec3* vector);
			Point3D* GetMovedCopyPtr(API::Data::Vec3& vector);
			Point3D* GetMovedCopyPtr(API::Data::Vec3* vector);
			API::Data::Vec3 ToVec3() const;
			API::Data::Vec3 operator-(const Point3D&);
		};
	}
}
#endif
