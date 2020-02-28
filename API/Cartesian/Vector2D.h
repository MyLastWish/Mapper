#ifndef VECTOR2D_H
#define VECTOR2D_H
#include "Object2D.h"
#include "Point2D.h"
#include <stdlib.h>
#include <cmath>
namespace API
{
	namespace Cartesian
	{
		class Point2D;
		enum Direction
		{
			LEFT,
			RIGHT
		};
		class Vector2D : public Object2D
		{
		private:
			API::Cartesian::Point2D _start;
			API::Cartesian::Point2D _end;

		public:
			Vector2D();
			Vector2D(const Vector2D& original);
			Vector2D(float x, float y);
			Vector2D(API::Cartesian::Point2D start, API::Cartesian::Point2D end);
			float GetX() const;
			float GetY() const;
			float GetLength() const;
			API::Cartesian::Point2D GetStart() const;
			API::Cartesian::Point2D GetEnd() const;
			void MoveStart(API::Data::Vec2 vec);
			void MoveEnd(API::Data::Vec2 vec);
			void SetPoints(API::Cartesian::Point2D start, API::Cartesian::Point2D end);
			Vector2D* GetPerpendicularCopy(Direction dir);
			Vector2D GetMultipliedCopy(float factor);
			void Invert();
			Vector2D& operator=(const Vector2D& original);
			float DotProduct(Vector2D& other);
		};
	}
}
#endif