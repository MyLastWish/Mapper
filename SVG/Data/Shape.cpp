#include "Shape.h"
SVG::Data::Shape::Shape()
{
	_lineWidth = 1.0f;
	_pathCount = 0;
}
SVG::Data::Shape::Shape(NSVGshape* originalShape) : Shape()
{
	_lineWidth = originalShape->strokeWidth;
	_strokeColor = _extractColor(&originalShape->stroke);
	_fillColor = _extractColor(&originalShape->fill);
	for (NSVGpath* path = originalShape->paths; path != NULL; path = path->next)
	{
		SVG::Data::Path* generatedPath = new SVG::Data::Path(path);
		_addPath(generatedPath);
	}
}

API::Graphic::Color SVG::Data::Shape::_extractColor(NSVGpaint* paint)
{
	float r, g, b, a;
	a = (float)((paint->color & 0xFF000000) >> 24);
	b = (float)((paint->color & 0x00FF0000) >> 16);
	g = (float)((paint->color & 0x0000FF00) >> 8);
	r = (float)((paint->color & 0x000000FF));
	r = r / 255.0f;
	g = g / 255.0f;
	b = b / 255.0f;
	a = a / 255.0f;
	return API::Graphic::Color(r, g, b, a);
}

void SVG::Data::Shape::_addPath(SVG::Data::Path* path)
{
	_paths.push_back(path);
	_pathCount++;
}

std::vector<Graphic::Graphic3D::Line*> SVG::Data::Shape::ToLines(unsigned& ct)
{
	std::vector<Graphic::Graphic3D::Line*> lines;
	for (int i = 0; i < _pathCount; i++)
	{
		unsigned count = 0;
		std::vector<Graphic::Graphic3D::Line*> gottenLines = _paths[i]->ToLines(_lineWidth, count);
		for (int j = 0; j < count; j++)
		{
			lines.push_back(gottenLines[j]);
		}
		ct += count;
	}
	return lines;
}