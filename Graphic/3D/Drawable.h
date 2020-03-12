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
			virtual void _prepare(); // Nadpisywalna funkcja w ktorej mozna np. przeskalowac obiekt.
			virtual void _draw(Shader*);
			void _generateBuffers(); // Podstawowa funkcja ktora przygotowuje bufory.
			void _invalidate();
			void _validate();
			friend void copyDrawables(Drawable*, Drawable*);
		public:
			Drawable();
			Drawable(std::vector<API::Cartesian::Point2D*>, std::vector<unsigned>);
			Drawable(std::vector<API::Cartesian::Point3D*>, std::vector<unsigned>, std::vector<API::Data::Vec3>);
			Drawable(Drawable&);
			void Draw(Graphic::Shader*);
			void PrepareToDraw();
			void SetRotation(API::Data::Vec3);
			void SetPosition(API::Data::Vec3);
		};
	}
}
#endif
