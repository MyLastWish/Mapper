#ifndef  RELATIVE_FACE_INFO_H
#define RELATIVE_FACE_INFO_H
#include "Data/Vec3.h"
#include "Cartesian/Point3D.h"
namespace Graphic
{
	namespace Graphic3D
	{
		namespace Infos
		{
			// Informacja o polozeniu wierzcholkow sciany.
			struct RelativeFaceInfo
			{
				API::Data::Vec3 Center;
				API::Data::Vec3 LowerLeftCornerTranslation;
				API::Data::Vec3 LowerRightCornerTranslation;
				API::Data::Vec3 UpperLeftCornerTranslation;
				API::Data::Vec3 UpperRightCornerTranslation;
			};
		}
	}
}
#endif // ! RELATIVE_FACE_INFO_H
