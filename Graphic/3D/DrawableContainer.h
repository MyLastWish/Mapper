#ifndef DRAWABLE_CONTAINER_H
#define DRAWABLE_CONTAINER_H
#include "Drawable.h"
#include "../API/Graphic/Positionable.h"
#include "Shader.h"
#include "DrawableObject.h"
#include <vector>
#include <type_traits>
namespace Graphic
{
	namespace Graphic3D
	{
		template <class C> // C musi dzedziczyc po Drawable.
		class DrawableContainer : public API::Graphic::Positionable, public Graphic::Graphic3D::Drawable
		{
			static_assert(std::is_base_of<Graphic::Graphic3D::DrawableObject, C>::value, "Class C must derive from DrawableObject");
		private:
			std::vector<C*> _contents;
			unsigned _count = 0;
		public:
			DrawableContainer(): Positionable()
			{
				_contents.clear();
				_count = 0;
			}
			DrawableContainer(std::vector<C> vec, unsigned count) : DrawableContainer()
			{
				for (int i = 0; i < count; i++)
				{
					Add(new C(vec[i]));
				}
			}
			DrawableContainer(std::vector<C*> vec, unsigned count) : DrawableContainer()
			{
				for (int i = 0; i < count; i++)
				{
					Add(vec[i]);
				}
			}
			void Draw(Shader* shader) override
			{
				for (int i = 0; i < _count; i++)
				{
					Graphic::Graphic3D::Drawable* obj = (Graphic::Graphic3D::Drawable*)_contents[i];
					obj->Draw(shader);
				}
			}
			void Add(C* element)
			{
				_contents.push_back(element);
				_count++;
			}

			void Remove(unsigned index)
			{
				if (index == _count - 1)
				{
					_contents.pop_back();
					return;
				}
				for (int i = index; i < _count - 1; i++)
				{
					_contents[i] = _contents[i + 1];
				}
				_contents.pop_back();
			}

			unsigned GetCount() const
			{
				return _count;
			}

			C* At(unsigned index)
			{
				if(index < 0 || index >= _count)
				{
					return nullptr;
				}
				return _contents[index];
			}
		};
	}
}
#endif