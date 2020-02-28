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
		protected:
			Point3D<T> _start;
			Point3D<T> _end;
		public:
			// Wektor ustalajacy punkty.
			Vector3D(Point3D<T> start, Point3D<T> end)
			{
				SetPoints(start, end);
			}
			// Konstruktor wyznaczajacy punkty na podstawie koordynatow (wyznacza je wzglednie!).
			Vector3D(T x, T y, T z) : Vector3D<T>(Point3D<T>(), Point3D<T>(x, y, z))
			{
			}
			T GetX() const  override
			{
				return _end.GetX() - _start.GetX();
			}
			T GetY() const  override
			{
				return _end.GetY() - _start.GetY();
			}
			T GetZ() const  override
			{
				return _end.GetZ() - _start.GetZ();
			}
			T GetLength() const
			{
				return std::sqrt(std::pow(_end.GetX() - _start.GetX(), 2), std::pow(_end.GetY() - _start.GetY(), 2), std::pow(_end.GetZ() - _start.GetZ(), 2));
			}
			void SetPoints(Point3D<T> start, Point3D<T> end)
			{
				_start = start;
				_end = end;
			}
			void MoveStartToPoint(Point3D<T> point)
			{
				SetPoints(point,
					API::Cartesian::Point3D<T>(
						point.GetX() + this->GetX(),
						point.GetY() + this->GetY(),
						point.GetZ() + this->GetZ()));
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
			Point3D<T> GetStart() const
			{
				return _start;
			}
			Point3D<T> GetEnd() const
			{
				return _end;
			}
			Vector3D<T>& operator=(const Vector3D<T>& original)
			{
				this->SetPoints(original.GetStart(), original.GetEnd());
				return *this;
			}
			Vector3D<T>* FindPerpendicular(Vector3D<T> normal)
			{
				T xThis = this->GetX();
				T yThis = this->GetY();
				T zThis = this->GetZ();
				T xNormal = normal.GetX();
				T yNormal = normal.GetY();
				T zNormal = normal.GetZ();
				return new Vector3D<T>(
					yThis * zNormal - yNormal * zThis,
					xNormal * zThis - xThis * zNormal,
					xThis * yNormal - xNormal * yThis);
			}
			Vector3D<T>* GetInvertedCopy()
			{
				return new Vector3D<T>(_end, _start);
			}
		};
	}
}
#endif