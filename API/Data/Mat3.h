#ifndef MAT3_H
#define MAT3_H
#include <vector>
#include "Vec3.h"
namespace API
{
	namespace Data
	{
		struct Vec3;
		// Klasa przechowujaca macierz 3x3.
		struct Mat3
		{
		private:
			float _matrix[9] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
		public:
			Mat3();
			// Konstruktor kopiujacy.
			Mat3(const Mat3&);
			// Konstruktor przyjmujacy wartosc dla kazdego elementu macierzy.
			Mat3(float);
			Vec3& operator*(const Vec3&);
			Mat3& operator*(const Mat3&);
			const float GetValue(int, int) const;
			void SetValue(int, int, float);
			void Eye(float = 1.0f);
			void XRotation(float);
			void YRotation(float);
			void ZRotation(float);
		};
	}
}
#endif // !MAT3_H
