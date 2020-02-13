#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <glad/glad.h>
#include "Shader.h"
#include "Cartesian/Point3D.h"
#include "Cartesian/Point2D.h"
#include "Graphic/Color.h"
#include <vector>
#include <glm/glm.hpp>
namespace Graphic
{
	namespace Graphic3D
	{
		template <typename T = float>
		class Drawable
		{
		protected:
			GLuint _vao = 0;
			GLuint _vbo = 0;
			GLuint _ebo = 0;
			std::vector<unsigned> _indices;
			std::vector<T> _readyCoords;
			API::Graphic::Color _color;
			unsigned _pointCount = 0;
			unsigned _indexCount = 0;
			bool _readyToDraw = false;
			virtual void _prepare() { } // Nadpisywalna funkcja w ktorej mozna np. przeskalowac obiekt.
			virtual void _draw(Shader* shader)
			{
				shader->Use();
				shader->Set4f("colorVector", _color.ToVec4());
				_glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
			void _generateBuffers() // Podstawowa funkcja ktora przygotowuje bufory.
			{
				glGenVertexArrays(1, &_vao);
				glGenBuffers(1, &_vbo);
				glGenBuffers(1, &_ebo);
				glBindVertexArray(_vao);
				glBindBuffer(GL_ARRAY_BUFFER, _vbo);
				glBufferData(GL_ARRAY_BUFFER, _readyCoords.size() * sizeof(3 * sizeof(T)), &_readyCoords[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned), &_indices[0], GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(3 * sizeof(T)), (void*)0);
				glBindVertexArray(0);
			}
			void _invalidate() { _readyToDraw = false; }
			void _validate() { _readyToDraw = true }
		public:
			Drawable() {}
			Drawable(std::vector<API::Cartesian::Point2D<T>*> points, std::vector<unsigned> indices)
			{
				for (int i = 0; i < indices.size(); i++)
				{
					_readyCoords.push_back(points[indices[i]]->GetX());
					_readyCoords.push_back(points[indices[i]]->GetY());
					_readyCoords.push_back(0);
					_pointCount++;
				}
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
				_generateBuffers();
				_prepare();
				_readyToDraw = true;
			}
		};
	}
}
#endif
