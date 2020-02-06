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
				API::Cartesian::Point2D<float> _start;
				API::Cartesian::Point2D<float> _firstControlPoint;
				API::Cartesian::Point2D<float> _secondControlPoint;
				API::Cartesian::Point2D<float> _end;

				void _setPoints(API::Cartesian::Point2D<float>, API::Cartesian::Point2D<float>, API::Cartesian::Point2D<float>, API::Cartesian::Point2D<float>);
				float _distanceToPoint(API::Cartesian::Point2D<float>);
			public:
				BezierCurve();
				BezierCurve(API::Cartesian::Point2D<float>, API::Cartesian::Point2D<float>, API::Cartesian::Point2D<float>, API::Cartesian::Point2D<float>);
				BezierCurve** DivideInTwo(float);
				// Podzial na mniejsze odcinki o minimalnej dlugosci. Drugi parametr przechowuje liczbe odcinkow.
				API::Cartesian::Point2D<float>* Subdivide(float, unsigned*);
				API::Cartesian::Point2D<float> GetEnd() const;
				API::Cartesian::Point2D<float> GetStart() const;
			};
		}
	}
}
#endif