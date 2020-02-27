#include "Shape.h"
SVG::Data::Shape::Shape()
{
	_lineWidth = 1.0f;
	_pathCount = 0;
}
SVG::Data::Shape::Shape(NSVGshape* originalShape) : Shape()
{
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
	_paths = (SVG::Data::Path**)realloc(_paths, ++_pathCount * sizeof(SVG::Data::Path));
	_paths[_pathCount - 1] = path;
}
std::vector<Graphic::Graphic3D::Mesh*> SVG::Data::Shape::ToMeshes()
{
	std::vector<Graphic::Graphic3D::Mesh*> meshes;
	for (int i = 0; i < _pathCount; i++)
	{
		meshes.push_back(_paths[i]->ToMesh());
	}
	return meshes;
}