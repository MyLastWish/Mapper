#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <glad/glad.h>
#include "Object3D.h"
#include "Point3D.h"
#include <math.h>
namespace API
{
	namespace Cartesian
	{
		template<typename T> class Point3D;
		template <typename T = float>
		class Vector3D : public Object3D<T>
		{
		private:
			API::Cartesian::Point3D<T> _start;
			API::Cartesian::Point3D<T> _end;
		public:
			Vector3D(API::Cartesian::Point3D<T> start, API::Cartesian::Point3D<T> end)
			{
				SetPoints(start, end);
			}
			Vector3D(T x, T y, T z) : Vector3D<T>(API::Cartesian::Point3D<T>((T)0.0f, (T)0.0f, (T)0.0f), API::Cartesian::Point3D(x, y, z))
			{
			}
			T GetLength() const
			{
				return std::sqrt(std::pow(_end.GetX() - _start.GetX(), 2), std::pow(_end.GetY() - _start.GetY(), 2), std::pow(_end.GetZ() - _start.GetZ(), 2));
			}
			void SetPoints(API::Cartesian::Point3D<T> start, API::Cartesian::Point3D<T> end)
			{
				_start = start;
				_end = end;
			}
			void MoveStart(Vector3D<T> vec)
			{
				_start.Move(vec);
			}
			void MoveEnd(Vector3D<T> vec)
			{
				_end.Move(vec);
			}
			void Move(Vector3D<T> vec)
			{
				MoveStart(vec);
				MoveEnd(vec);
			}
			Vector3D<T>& operator=(const Vector3D<T>& original)
			{
				this->SetPoints(original.GetStart(), original.GetEnd());
				return *this;
			}
		};
	}
}
#endif