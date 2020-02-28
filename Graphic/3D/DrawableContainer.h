#ifndef DRAWABLE_CONTAINER_H
#define DRAWABLE_CONTAINER_H
#include "Drawable.h"
#include "Shader.h"
#include <vector>
#include <type_traits>
namespace Graphic
{
	namespace Graphic3D
	{
		template <class C> // C musi dzedziczyc po Drawable.
		class DrawableContainer
		{
			static_assert(std::is_base_of<Graphic::Graphic3D::Drawable, C>::value, "Class C must derive from Drawable");
		private:
			std::vector<C*> _contents;
			unsigned _count = 0;
		public:
			DrawableContainer()
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
			void Draw(Shader* shader)
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
		};
	}
}
#endif