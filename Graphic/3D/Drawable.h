#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <glad/glad.h>
#include "Shader.h"
#include "Cartesian/Point3D.h"
#include "Cartesian/Point2D.h"
#include "Cartesian/Vector3D.h"
#include "Graphic/Color.h"
#include <vector>
#include <glm/glm.hpp>
namespace Graphic
{
	namespace Graphic3D
	{
		class Drawable
		{
		protected:
			GLuint _vao = 0;
			GLuint _vbo = 0;
			GLuint _ebo = 0;
			API::Data::Vec3 _position;
			API::Data::Vec3 _rotation;
			std::vector<unsigned> _indices;
			std::vector<float> _coords;
			std::vector<API::Data::Vec3> _normals;
			API::Graphic::Color _color;
			unsigned _coordCount = 0;
			unsigned _indexCount = 0;
			bool _readyToDraw = false;
			virtual void _prepare() { } // Nadpisywalna funkcja w ktorej mozna np. przeskalowac obiekt.
			virtual void _draw(Shader* shader)
			{
				shader->Use();
				shader->Set4f("colorVector", _color.ToVec4());
				glBindVertexArray(_vao);
				glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
			void _generateBuffers() // Podstawowa funkcja ktora przygotowuje bufory.
			{
				glGenVertexArrays(1, &_vao);
				glGenBuffers(1, &_vbo);
				glGenBuffers(1, &_ebo);
				glBindVertexArray(_vao);
				glBindBuffer(GL_ARRAY_BUFFER, _vbo);
				glBufferData(GL_ARRAY_BUFFER, _coords.size() * (3 * sizeof(float)), &_coords[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned), &_indices[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glBindVertexArray(0);
			}
			void _invalidate() { _readyToDraw = false; }
			void _validate() { _readyToDraw = true; }
			friend void copyDrawables(Drawable* original, Drawable* copy);
		public:
			Drawable() {}
			Drawable(std::vector<API::Cartesian::Point2D*> points, std::vector<unsigned> indices)
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
			Drawable(std::vector<API::Cartesian::Point3D*> points, std::vector<unsigned> indices, std::vector<API::Data::Vec3> normals)
			{
				for (int i = 0; i < indices.size(); i++)
				{
					_coords.push_back(points[indices[i]]->GetX());
					_coords.push_back(points[indices[i]]->GetY());
					_coords.push_back(points[indices[i]]->GetZ());
					_normals.push_back(normals[i]);
					_coordCount += 3;
				}
				_indices = indices;
				_indexCount = _coordCount / 3u;
				_normals = normals;
			}
			Drawable(Drawable& original)
			{
				copyDrawables(&original, this);
			}
			void Draw(Graphic::Shader* shader)
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
			void PrepareToDraw()
			{
				_prepare();
				_generateBuffers();
				_validate();
			}
		};
		void copyDrawables(Drawable* original, Drawable* copy)
		{
			copy->_color = original->_color;
			copy->_coordCount = original->_coordCount;
			copy->_indexCount = original->_indexCount;
			copy->_coords = original->_coords;
			copy->_indices = original->_indices;
			copy->_normals = original->_normals;
			copy->_readyToDraw = false;
		}
	}
}
#endif
