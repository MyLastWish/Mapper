#ifndef MAT4_H
#define MAT4_H
#include "Vec4.h"
#include "Mat3.h"
#include "Vec3.h"
#include "../../Include/glm/glm.hpp"
#include <string>
namespace API
{
	namespace Data
	{
		struct Mat4
		{
		private:
			API::Data::Vec4 _columns[4] = { API::Data::Vec4(), API::Data::Vec4(), API::Data::Vec4(), API::Data::Vec4() };
		public:
			Mat4();
			Mat4(const Mat4&);
			Mat4(float);
			Mat4(const glm::mat4&);
			Vec4 operator*(const API::Data::Vec4&);
			Mat4 operator*(const Mat4&);
			API::Data::Vec4 operator[](const int&) const;
			API::Data::Vec4& operator[](const int&);
			const float GetValue(int, int) const;
			void SetValue(int, int, float);
			void Eye(float = 1.0f);
			// Stworzenie macierzy transformacji na podstawie macierzy rotacji i wektora przesuniec.
			void MakeTranformationMatrix(const API::Data::Mat3&, const API::Data::Vec3&);
			// Zwroc wskaznik na macierz. 
			const float* GetMatrixPointer() const;
			glm::mat4 ToGLM();
		};
	}
}
#endif // !MAT4_H
