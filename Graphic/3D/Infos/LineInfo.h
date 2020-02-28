#ifndef LINE_INFO_H
#define LINE_INFO_H
#include "Cartesian/Point3D.h"
#include "Cartesian/Vector3D.h"
namespace Graphic
{
	namespace Graphic3D
	{
		namespace Infos
		{
			struct LineInfo // Info nt. majacej byc stworzonej sciezki. Istotne jest, ze obiekt linii budowany jest od dolu - wskazane koordynaty odcinka sa w podstawie, a reszta budowana jest wzdloz normalnej.
			{
				API::Cartesian::Point3D<float> Start;
				API::Cartesian::Point3D<float> End;
				API::Cartesian::Vector3D<float> StartFaceNormal;
				API::Cartesian::Vector3D<float> EndFaceNormal;
				API::Cartesian::Vector3D<float> LineNormal;
			};
		}
	}
}
#endif