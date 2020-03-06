#ifndef LINE_INFO_H
#define LINE_INFO_H
#include "Cartesian/Point3D.h"
#include "Cartesian/Vector3D.h"
#include "Data/Vec3.h"
namespace Graphic
{
	namespace Graphic3D
	{
		namespace Infos
		{
			struct LineInfo // Info nt. majacej byc stworzonej sciezki. Istotne jest, ze obiekt linii budowany jest od dolu - wskazane koordynaty odcinka sa w podstawie, a reszta budowana jest wzdloz normalnej.
			{
				API::Cartesian::Point3D Start;
				float Length;
				API::Data::Vec3 StartFaceNormal;
				API::Data::Vec3 EndFaceNormal;
			};
		}
	}
}
#endif