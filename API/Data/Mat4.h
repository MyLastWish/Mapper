#ifndef MAT4_H
#define MAT4_H
#include "Vec4.h"
namespace API
{
	namespace Data
	{
		struct Mat4
		{
		private:
			float _matrix[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
		public:
			Mat4();
			Mat4(const Mat4&);
			Mat4(float);
			Vec4& operator*(const API::Data::Vec4&);
			Mat4& operator*(const Mat4&);
			float GetValue(int, int) const;
			void SetValue(int, int, float);
			void Eye(float = 1.0f);
		};
	}
}
#endif // !MAT4_H