#ifndef SVG_IMAGE_H
#define SVG_IMAGE_H
#include <vector>
#include "Shape.h"
namespace SVG
{
	namespace Data
	{
		class Image
		{
		private:
			char* _sourcePath = 0;
			SVG::Data::Shape** _shapes;
			unsigned _shapeCount;
		public:
			Image();
			Image(const char*);
			void _addShape(SVG::Data::Shape*);
		};
	}
}
#endif