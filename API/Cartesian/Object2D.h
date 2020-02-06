#ifndef OBJECT2D_H
#define OBJECT2D_H
namespace API
{
	namespace Cartesian
	{
		template <typename T = float>
		class Object2D
		{
		protected:
			T _x;
			T _y;
		public:
			Object2D();
			Object2D(T x, T y) { SetCoords2D(x, y); }
			void SetCoords2D(T x, T y)
			{
				_x = x;
				_y = y;
			}
			virtual T GetX() const { return _x; }
			virtual T GetY() const { return _y; }
			virtual bool operator==(const Object2D& other)
			{
				return _x == other.GetX() && _y == other.GetY();
			}

			virtual bool operator!=(const Object2D& other)
			{
				return _x != other.GetX() || _y != other.GetY();
			}
		};
	}
}
#endif