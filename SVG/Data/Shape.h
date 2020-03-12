#ifndef SVG_SHAPE_H
#define SVG_SHAPE_H
#include "Path.h"
#include "Graphic/Color.h"
#include "3D/Line.h"
namespace SVG
{
	namespace Data
	{
		class Shape
		{
		private:
			SVG::Data::Path** _paths;
			unsigned _pathCount;
			API::Graphic::Color _fillColor;
			API::Graphic::Color _strokeColor;
			float _lineWidth;

			void _addPath(SVG::Data::Path*);
			API::Graphic::Color _extractColor(NSVGpaint*);
		public:
			Shape();
			Shape(NSVGshape*);
			std::vector<Graphic::Graphic3D::Line*> ToLines(unsigned&);
		};
	}
}
#endif