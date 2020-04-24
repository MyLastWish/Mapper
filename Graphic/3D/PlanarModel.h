#ifndef PLANAR_MODEL_H
#define PLANAR_MODEL_H
#include "DrawableContainer.h"
#include "Line.h"
namespace Graphic
{
	namespace Graphic3D
	{
		class PlanarModel : public DrawableContainer
		{
		public:
			PlanarModel();
			PlanarModel(std::vector<Graphic::Graphic3D::DrawableObject*>, unsigned);
			PlanarModel(Line*);
		};
	}
}
#endif // !PLANAR_MODEL_H
