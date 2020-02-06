#ifndef SVG_PATH_H
#define SVG_PATH_H
#include "Cartesian/Point2D.h"
#include "NanoSVG.h"
#include "Cartesian/Curves/BezierCurve.h"
namespace SVG
{
	namespace Data
	{
		class Path
		{
		private:
			unsigned* _indices;
			API::Cartesian::Point2D<float>* _points;
			unsigned _indexCount;
			unsigned _pointCount;
		public:
			Path();
			Path(NSVGpath*);
			void _addPointAndIndex(API::Cartesian::Point2D<float>);
		};
	}
}
#endif