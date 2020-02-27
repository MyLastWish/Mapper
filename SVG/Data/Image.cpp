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

Graphic::Graphic3D::Model* SVG::Data::Image::To3DModel()
{
	std::vector<Graphic::Graphic3D::Mesh*> meshes;
	for (unsigned i = 0; i < _shapeCount; i++)
	{
		std::vector<Graphic::Graphic3D::Mesh*> retreivedMeshes;
		retreivedMeshes = _shapes[i]->ToMeshes();
		for (unsigned j = 0; j < retreivedMeshes.size(); j++)
		{
			meshes.push_back(retreivedMeshes[j]);
		}
	}
	return new Graphic::Graphic3D::Model(meshes, meshes.size()); // TODO: Poprawic metode liczenia mesh.
}