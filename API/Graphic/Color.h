#ifndef COLOR_H
#define COLOR_H
namespace API
{
	namespace Graphic
	{
		class Color
		{
		private:
			unsigned _red;
			unsigned _green;
			unsigned _blue;
			unsigned _alpha;

			template <typename T>
			T _limit(T val, T lower, T upper)
			{
				if (val > upper) return upper;
				else if (val < lower) return lower;
				else return val;
			}
		public:
			Color();
			Color(unsigned, unsigned, unsigned, unsigned = 255);
			Color(float, float, float, float = 1.0f);
			Color(double, double, double, double = 1.0);
			void Set(unsigned, unsigned, unsigned, unsigned = 255);
		};
	}
}
#endif