#ifndef MAT3_H
#define MAT3_H
#include <vector>
#include <assert.h>
#include <stdlib.h>
namespace API
{
	namespace Data
	{
		struct Vec3;
		// Klasa przechowujaca macierz 3x3.
		struct Mat3
		{
		private:
			Vec3* _columns = nullptr;
		public:
			Mat3();
			// Konstruktor kopiujacy.
			Mat3(const Mat3&);
			// Konstruktor przyjmujacy wartosc dla kazdego elementu macierzy.
			Mat3(float);
			~Mat3();
			Vec3 operator*(const Vec3&);
			Mat3 operator*(const Mat3&);
			Vec3& operator[](const int&);
			Vec3 operator[](const int&) const;
			Mat3& operator=(const Mat3&);
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
