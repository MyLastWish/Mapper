#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H
#include "Cartesian/Point2D.h"
#include "Cartesian/Vector2D.h"
#include <vector>
namespace API
{
	namespace Cartesian
	{
		namespace Curves
		{
			class BezierCurve
			{
			private:
				API::Cartesian::Point2D _start;
				API::Cartesian::Point2D _firstControlPoint;
				API::Cartesian::Point2D _secondControlPoint;
				API::Cartesian::Point2D _end;

				void _setPoints(API::Cartesian::Point2D, API::Cartesian::Point2D, API::Cartesian::Point2D, API::Cartesian::Point2D);
				float _distanceToPoint(API::Cartesian::Point2D);
				bool _valueInToleranceRangeFrom(float, float, float);
			public:
				BezierCurve();
				BezierCurve(API::Cartesian::Point2D, API::Cartesian::Point2D, API::Cartesian::Point2D, API::Cartesian::Point2D);
				BezierCurve** DivideInTwo(float);
				// Podzial na mniejsze odcinki o minimalnej dlugosci. Drugi parametr przechowuje liczbe odcinkow.
				std::vector<API::Cartesian::Point2D*> Subdivide(float, unsigned*);
				API::Cartesian::Point2D GetEnd() const;
				API::Cartesian::Point2D GetStart() const;
			};
		}
	}
}
#endif