#ifndef LINE_H
#define LINE_H
#include <vector>
#include <math.h>
#include <functional>
#include "Drawable.h"
#include "Cartesian/Point3D.h"
#include "Cartesian/Vector3D.h"
#include "Infos/LineInfo.h"
#include "Infos/RelativeFaceInfo.h"
namespace Graphic
{
	namespace Graphic3D
	{
		class Line : Drawable
		{
		private:
			// Metoda rysowania sciezki wzdloz odcinka miedzy dwoma punktami.
			void _drawAlong(Graphic::Graphic3D::Infos::LineInfo*, float, float); // Najwazniejsza metoda klasy!
			// Metoda majaca wyznaczyc punkty scian na koncach linii.
			Graphic::Graphic3D::Infos::RelativeFaceInfo _getEndFaceInfo(API::Data::Vec3, API::Data::Vec3, float, float);
		public:
			Line();
			Line(API::Cartesian::Point3D, float, float);
		};
	}
}
#endif