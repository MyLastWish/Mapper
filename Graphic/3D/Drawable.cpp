#include "Drawable.h"

Graphic::Graphic3D::Drawable::Drawable() : Graphic::Graphic3D::Positionable()
{

}

void Graphic::Graphic3D::Drawable::Draw(Graphic::Shader* shader)
{
	UpdateTransformation(shader);
	_drawObject(shader);
}

void Graphic::Graphic3D::Drawable::_drawObject(Graphic::Shader* shader)
{
	
}