#include "Image.h"
SVG::Data::Image::Image()
{
	_shapeCount = 0;
	_sourcePath = 0;
	_shapes.clear();
}

SVG::Data::Image::Image(const char* path) : Image()
{
	NSVGimage* originalImage = nsvgParseFromFile(path, "px", 96.0f);
	if (originalImage == nullptr)
	{
		return;
	}
	for (NSVGshape* shape = originalImage->shapes; shape != nullptr; shape = shape->next)
	{
		SVG::Data::Shape* generatedShape = new SVG::Data::Shape(shape);
		_addShape(generatedShape);
	}
}

void SVG::Data::Image::_addShape(SVG::Data::Shape* shape)
{
	_shapes.push_back(shape);
	_shapeCount++;
}

Graphic::Graphic3D::PlanarModel* SVG::Data::Image::ToPlanarModel()
{
	std::vector<Graphic::Graphic3D::DrawableObject*> meshes;
	unsigned count = 0;
	for (unsigned i = 0; i < _shapeCount; i++)
	{
		unsigned retreivedCount = 0;
		std::vector<Graphic::Graphic3D::Line*> retreivedLines;
		retreivedLines = _shapes[i]->ToLines(retreivedCount);
		for (unsigned j = 0; j < retreivedCount; j++)
		{
			meshes.push_back(retreivedLines[j]);
			count++;
		}
	}
	return new Graphic::Graphic3D::PlanarModel(meshes, count);
}