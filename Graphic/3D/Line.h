#ifndef LINE_H
#define LINE_H
#include <vector>
#include "Drawable.h"
#include "Cartesian/Point3D.h"
#include "Cartesian/Vector3D.h"
#include "Infos/LineInfo.h"
namespace Graphic
{
	namespace Graphic3D
	{
		class Line : Drawable<float>
		{
		private:
			// Metoda rysowania sciezki wzdloz odcinka miedzy dwoma punktami.
			std::vector<float> _drawAlong(Graphic::Graphic3D::Infos::LineInfo*, float); // Najwazniejsza metoda klasy!
		public:
			Line();
		};
	}
}
#endif