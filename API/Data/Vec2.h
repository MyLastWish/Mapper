#ifndef VEC2_H
#define VEC2_H
namespace API
{
	namespace Data
	{
		struct Vec2
		{
			float X = 0.0f;
			float Y = 0.0f;
			Vec2();
			Vec2(float, float);
			Vec2(Vec2*);
			// Zamienia zwrot wektora na przeciwny.
			void Invert();
			// Zwraca wskaznik na wektor o przeciwnym zwrocie.
			Vec2* GetInvertedCopyPtr();
			// Zwraca obiekt wektora o przeciwnym zwrocie.
			Vec2 GetInvertedCopy();
		};
	}
}
#endif