#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include "DrawableContainer.h"
namespace Graphic
{
	namespace Graphic3D
	{
		class Model : public DrawableContainer<Mesh*>
		{
		public:
			Model();
			Model(std::vector<Mesh*>);
			Model(Mesh*);
		};
	}
}

#endif