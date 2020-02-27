#ifndef SVG_PATH_H
#define SVG_PATH_H
#include <vector>
#include "Cartesian/Point2D.h"
#include "NanoSVG.h"
#include "Cartesian/Curves/BezierCurve.h"
#include "3D/Mesh.h"
namespace SVG
{
	namespace Data
	{
		class Path
		{
		private:
			std::vector<unsigned> _indices;
			std::vector<API::Cartesian::Point2D<float>*> _points;
			unsigned _indexCount = 0;
			unsigned _pointCount = 0;
		public:
			Path();
			Path(NSVGpath*);
			void _addPointAndIndex(API::Cartesian::Point2D<float>*);
			Graphic::Graphic3D::Mesh* ToMesh();
		};
	}
}
#endif