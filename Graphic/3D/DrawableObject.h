#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H
#include <glad/glad.h>
#include "Shader.h"
#include "Cartesian/Point3D.h"
#include "Cartesian/Point2D.h"
#include "Cartesian/Vector3D.h"
#include "Graphic/Color.h"
#include "Graphic/Positionable.h"
#include "Data/Mat4.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Drawable.h"
namespace Graphic
{
	namespace Graphic3D
	{
		class DrawableObject : public API::Graphic::Positionable, public Graphic::Graphic3D::Drawable
		{
		protected:
			GLuint _vao = 0;
			GLuint _vbo = 0;
			GLuint _ebo = 0;
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
			friend void copyDrawableObjects(DrawableObject*, DrawableObject*);
		public:
			DrawableObject();
			DrawableObject(std::vector<API::Cartesian::Point2D*>, std::vector<unsigned>);
			DrawableObject(std::vector<API::Cartesian::Point3D*>, std::vector<unsigned>, std::vector<API::Data::Vec3>);
			DrawableObject(DrawableObject&);
			void Draw(Graphic::Shader*) override;
			void PrepareToDraw();
		};
	}
}
#endif
