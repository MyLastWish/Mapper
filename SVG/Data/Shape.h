#ifndef SVG_SHAPE_H
#define SVG_SHAPE_H
#include <vector>
#include "Path.h"
#include "../Graphic/Color.h"
#include "3D/Line.h"
namespace SVG
{
	namespace Data
	{
		class Shape
		{
		private:
			std::vector<SVG::Data::Path*> _paths;
			unsigned _pathCount;
			Graphic::Color _fillColor;
			Graphic::Color _strokeColor;
			float _lineWidth;

			void _addPath(SVG::Data::Path*);
			Graphic::Color _extractColor(NSVGpaint*);
		public:
			Shape();
			Shape(NSVGshape*);
			std::vector<Graphic::Graphic3D::Line*> ToLines(unsigned&);
		};
	}
}
#endif