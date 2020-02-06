#ifndef VECTOR2D_H
#define VECTOR2D_H
#include "Object2D.h"
#include "Point2D.h"
#include <math.h>
namespace API
{
	namespace Cartesian
	{
		template <typename T> class Point2D;
		enum Direction
		{
			LEFT,
			RIGHT
		};
		template <typename T = float>
		class Vector2D : public API::Cartesian::Object2D<T>
		{
		private:
			API::Cartesian::Point2D<T> _start;
			API::Cartesian::Point2D<T> _end;

		public:
			Vector2D() {}
			Vector2D(const Vector2D<T>& original) { SetPoints(original.GetStart(), original.GetEnd()); }
			Vector2D(T x, T y) { SetCoords2D(x, y); }
			Vector2D(API::Cartesian::Point2D<T> start, API::Cartesian::Point2D<T> end) { _start = start; _end = end; }
			T GetX() { return _end.GetX() - _start.GetX(); }
			T GetY() { return _end.GetY() - _start.GetY(); }
			T GetLength() const { return std::sqrt(std::pow(GetX(), 2), std::pow(GetY(), 2)); }
			API::Cartesian::Point2D<T> GetStart() const { return _start; }
			API::Cartesian::Point2D<T> GetEnd() const { return _end; }
			void MoveStart(Vector2D<T> vec)
			{
				_start.Move(vec);
			}
			void MoveEnd(Vector2D<T> vec)
			{
				_end.Move(vec);
			}
			void SetPoints(API::Cartesian::Point2D<T> start, API::Cartesian::Point2D<T> end)
			{
				_start = start;
				_end = end;
			}
			Vector2D* GetPerpendicularCopy(Direction dir)
			{
				Vector2D<T>* copy = *this;
				Vector2D<T> crossResult;
				Vector2D<T> planarVector = Vector2D<T>((T)0.0f, (T)0.0f, (T)1.0f);
				if (dir == Direction::RIGHT)
				{
					planarVector.Invert();
				}
				//crossResult = _crossProduct(copy, planarVector);
				return crossResult;
			}
			Vector2D* GetMultipliedCopy(float factor)
			{
				Vector2D* copy = new Vector2D<T>((*this));
				copy.MoveEnd(Vector2D<T>((T)copy.GetX() * (T)(1.0f - factor), (T)copy.GetY() * (T)(1.0f - factor)));
			}
			void Invert()
			{
				SetPoints(_end, _start);
			}
			Vector2D<T>& operator=(const Vector2D<T>& original)
			{
				this->SetPoints(original.GetStart(), original.GetEnd());
				return *this;
			}
		};
	}
}
#endif