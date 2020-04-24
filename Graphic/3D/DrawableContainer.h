#ifndef DRAWABLE_CONTAINER_H
#define DRAWABLE_CONTAINER_H
#include "Drawable.h"
#include "Positionable.h"
#include "Shader.h"
#include "DrawableObject.h"
#include <vector>
#include <type_traits>
namespace Graphic
{
	namespace Graphic3D
	{
		class DrawableContainer : public Graphic::Graphic3D::Drawable
		{
		private:
			std::vector<Graphic::Graphic3D::DrawableObject*> _contents;
			unsigned _count = 0;
			void _drawObject(Shader* shader) override;
		public:
			DrawableContainer();
			DrawableContainer(std::vector<Graphic::Graphic3D::DrawableObject>, unsigned);
			DrawableContainer(std::vector<Graphic::Graphic3D::DrawableObject*>, unsigned);
			void Add(Graphic::Graphic3D::DrawableObject*);
			void Remove(unsigned);
			unsigned GetCount() const;
			Graphic::Graphic3D::DrawableObject* At(unsigned);
		};
	}
}
#endif