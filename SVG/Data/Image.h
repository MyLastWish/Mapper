#ifndef SVG_IMAGE_H
#define SVG_IMAGE_H
#include <vector>
#include "Shape.h"
#include "3D/Model.h"
#include "3D/Mesh.h"
namespace SVG
{
	namespace Data
	{
		class Image
		{
		private:
			char* _sourcePath = 0;
			std::vector<SVG::Data::Shape*> _shapes;
			unsigned _shapeCount;
			void _addShape(SVG::Data::Shape*);
		public:
			Image();
			Image(const char*);
			Graphic::Graphic3D::Model* To3DModel();
		};
	}
}
#endif