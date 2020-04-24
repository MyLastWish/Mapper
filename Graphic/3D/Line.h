#ifndef LINE_H
#define LINE_H
#include <vector>
#include <math.h>
#include <functional>
#include "DrawableObject.h"
#include "Cartesian/Point3D.h"
#include "Cartesian/Vector3D.h"
#include "Infos/LineInfo.h"
#include "Infos/RelativeFaceInfo.h"
#include "Data/Mat3.h"
namespace Graphic
{
	namespace Graphic3D
	{
		class Line : public DrawableObject
		{
		private:
			// Metoda rysowania sciezki wzdloz odcinka miedzy dwoma punktami.
			void _drawAlong(Graphic::Graphic3D::Infos::LineInfo*); // Najwazniejsza metoda klasy!
			// Metoda majaca wyznaczyc punkty scian na koncach linii.
			Graphic::Graphic3D::Infos::RelativeFaceInfo _getEndFaceInfo(API::Data::Vec3, API::Data::Vec3, float, float);
			friend void copyLines(Line*, Line*);
		public:
			Line();
			Line(const Line&);
			Line(Graphic::Graphic3D::Infos::LineInfo*);
			~Line();
		};
		void copyLines(Line*, Line*);
	}
}
#endif