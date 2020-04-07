#include "Mat4.h"

API::Data::Mat4::Mat4()
{
}
API::Data::Mat4::Mat4(const Mat4& original)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			SetValue(i, j, original.GetValue(i, j));
		}
	}
}
API::Data::Mat4::Mat4(float value)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			SetValue(i, j, value);
		}
	}
}
API::Data::Vec4& API::Data::Mat4::operator*(const API::Data::Vec4& vector)
{
	API::Data::Vec4 result = API::Data::Vec4();
	result.X = _matrix[0] * vector.X + _matrix[1] * vector.Y + _matrix[2] * vector.Z + _matrix[3] * vector.W;
	result.Z = _matrix[4] * vector.X + _matrix[5] * vector.Y + _matrix[6] * vector.Z + _matrix[7] * vector.W;
	result.Y = _matrix[8] * vector.X + _matrix[9] * vector.Y + _matrix[10] * vector.Z + _matrix[11] * vector.W;
	result.W = _matrix[12] * vector.X + _matrix[13] * vector.Y + _matrix[14] * vector.Z + _matrix[15] * vector.W;
	return result;
}
API::Data::Mat4& API::Data::Mat4::operator*(const Mat4& otherMatrix)
{
	API::Data::Mat4 resultMatrix = API::Data::Mat4();
	for (int i = 0; i < 4; i++) // Iteracja po wierszach macierzy wynikowej.
	{
		for (int j = 0; j < 4; j++) // Iteracja po kolumnach macierzy wynikowej.
		{
			float result = 0;
			for (int k = 0; k < 4; k++)
			{
				result += GetValue(i, k) * otherMatrix.GetValue(k, j);
			}
			SetValue(i, j, result);
		}
	}
	return resultMatrix;
}
const float API::Data::Mat4::GetValue(int row, int column) const
{
	if (column < 0 || column > 3 || row < 0 || row > 3)
	{
		return 0; // TODO: Dodac wywalanie bledu.
	}
	return _matrix[row * 4 + column];
}

void API::Data::Mat4::SetValue(int row, int column, float value)
{
	if (column < 0 || column > 3 || row < 0 || row > 3)
	{
		return; // TODO: Dodac wywalanie bledu.
	}
	_matrix[row * 4 + column] = value;
}

void API::Data::Mat4::Eye(float value)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				SetValue(i, j, value);
			}
			else
			{
				SetValue(i, j, 0.0f);
			}
		}
	}
}

void API::Data::Mat4::MakeTranformationMatrix(const API::Data::Mat3& rotations, const API::Data::Vec3& translations)
{
	Eye(1.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SetValue(i, j, rotations.GetValue(i, j));
		}
	}
	SetValue(0, 0, translations.X);
	SetValue(0, 0, translations.Y);
	SetValue(0, 0, translations.Z);
}

const float* API::Data::Mat4::GetMatrixPointer() const
{
	return _matrix;
}
