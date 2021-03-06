#include "3D/DrawableObject.h"
void Graphic::Graphic3D::DrawableObject::_draw(Shader* shader)
{
	shader->Use();
	shader->Set4f("colorVector", _color.ToVec4());
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, (void*)_indices[0]);
	glBindVertexArray(0);
}
void Graphic::Graphic3D::DrawableObject::_prepare()
{
	
}
void Graphic::Graphic3D::DrawableObject::_generateBuffers() // Podstawowa funkcja ktora przygotowuje bufory.
{
	if (!_indexCount) return;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _coordCount * sizeof(float), &_coords[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(unsigned), &_indices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);
}

void Graphic::Graphic3D::DrawableObject::_invalidate()
{
	_readyToDraw = false;
}
void Graphic::Graphic3D::DrawableObject::_validate()
{
	_readyToDraw = true;
}

Graphic::Graphic3D::DrawableObject::DrawableObject()
{
}

Graphic::Graphic3D::DrawableObject::DrawableObject(std::vector<API::Cartesian::Point2D*> points, std::vector<unsigned> indices)
{
	for (int i = 0; i < indices.size(); i++)
	{
		_coords.push_back(points[indices[i]]->GetX());
		_coords.push_back(points[indices[i]]->GetY());
		_coords.push_back(0);
		_normals.push_back(API::Data::Vec3(0.0f, 0.0f, 1.0f));
		_coordCount += 3;
	}
	_indices = indices;
	_indexCount = _coordCount / 3u;
}
Graphic::Graphic3D::DrawableObject::DrawableObject(std::vector<API::Cartesian::Point3D*> points, std::vector<unsigned> indices, std::vector<API::Data::Vec3> normals)
{
	for (int i = 0; i < points.size(); i++)
	{
		_coords.push_back(points[i]->GetX());
		_coords.push_back(points[i]->GetY());
		_coords.push_back(points[i]->GetZ());
		_normals.push_back(normals[i]);
		_coordCount += 3;
	}
	_indices = indices;
	_indexCount = indices.size();
	_normals = normals;
}
Graphic::Graphic3D::DrawableObject::DrawableObject(DrawableObject& original)
{
	copyDrawableObjects(&original, this);
}
void Graphic::Graphic3D::DrawableObject::_drawObject(Graphic::Shader* shader)
{
	if (shader == nullptr)
	{
		return;
	}
	if (!_readyToDraw)
	{
		PrepareToDraw();
	}
	_draw(shader);
}

void Graphic::Graphic3D::DrawableObject::PrepareToDraw()
{
	_prepare();
	_generateBuffers();
	_validate();
}

void Graphic::Graphic3D::copyDrawableObjects(DrawableObject* original, DrawableObject* copy)
{
	copy->_color = original->_color;
	copy->_coordCount = original->_coordCount;
	copy->_indexCount = original->_indexCount;
	copy->_coords = original->_coords;
	copy->_indices = original->_indices;
	copy->_normals = original->_normals;
	copy->_rotation = original->_rotation;
	copy->_position = original->_position;
	copy->_readyToDraw = false;
}



