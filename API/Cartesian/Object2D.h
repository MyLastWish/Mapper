#ifndef OBJECT2D_H
#define OBJECT2D_H
#include <vector>
namespace API
{
	namespace Cartesian
	{
		class Object2D
		{
		protected:
			float _x;
			float _y;
		public:
			Object2D();
			Object2D(float x, float y);
			void SetCoords2D(float x, float y);
			virtual float GetX() const;
			virtual float GetY() const;
			virtual bool operator==(const Object2D&);
			virtual bool operator!=(const Object2D&);
			virtual std::vector<float> GetCoordsInArray();
		};
	}
}
#endif