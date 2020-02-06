#include "Image.h"
SVG::Data::Image::Image()
{
	_shapeCount = 0;
	_shapes = 0;
	_sourcePath = 0;
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
	_shapes = (SVG::Data::Shape**)realloc(_shapes, ++_shapeCount * sizeof(SVG::Data::Shape*));
	_shapes[_shapeCount - 1] = shape;
}