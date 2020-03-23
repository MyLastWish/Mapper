#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "Object3D.h"
#include "Point3D.h"
#include "../Data/Vec3.h"
#include <math.h>
namespace API
{
	namespace Cartesian
	{
		class Vector3D : public Object3D
		{
		protected:
			API::Cartesian::Point3D _start;
			API::Cartesian::Point3D _end;
		public:
			Vector3D();
			// Wektor ustalajacy punkty.
			Vector3D(API::Cartesian::Point3D start, API::Cartesian::Point3D end);
			Vector3D(API::Cartesian::Point3D start, API::Data::Vec3 vec);
			float GetX() const  override;
			float GetY() const  override;
			float GetZ() const  override;
			float GetLength() const;
			void SetPoints(API::Cartesian::Point3D start, API::Cartesian::Point3D end);
			void MoveStart(API::Data::Vec3 vec);
			void MoveEnd(API::Data::Vec3 vec);
			void Move(API::Data::Vec3 vec);
			API::Cartesian::Point3D GetStart() const;
			API::Cartesian::Point3D GetEnd() const;
			Vector3D& operator=(const Vector3D& original);
			Vector3D* FindPerpendicular(Vector3D normal);
			Vector3D GetInvertedCopy();
			Vector3D* GetInvertedCopyPtr();
			API::Data::Vec3 GetVectorCoords() const;
		};
	}
}
#endif
