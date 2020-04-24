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
			_columns[j][i] = original[j][i];
		}
	}
}
API::Data::Mat4::Mat4(float value)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_columns[j][i] = value;
		}
	}
}

API::Data::Mat4::Mat4(const glm::mat4& matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_columns[j][i] = matrix[j][i];
		}
	}
}
API::Data::Vec4 API::Data::Mat4::operator*(const API::Data::Vec4& vector)
{
	API::Data::Vec4 result = API::Data::Vec4();
	result.X = _columns[0].X * vector.X + _columns[1].X * vector.Y + _columns[2].X * vector.Z + _columns[3].X * vector.W;
	result.Z = _columns[0].Y * vector.X + _columns[1].Y * vector.Y + _columns[2].Y * vector.Z + _columns[3].Y * vector.W;
	result.Y = _columns[0].Z * vector.X + _columns[1].Z * vector.Y + _columns[2].Z * vector.Z + _columns[3].Z * vector.W;
	result.W = _columns[0].W * vector.X + _columns[1].W * vector.Y + _columns[2].W * vector.Z + _columns[3].W * vector.W;
	return result;
}
API::Data::Mat4 API::Data::Mat4::operator*(const Mat4& otherMatrix)
{
	API::Data::Mat4 resultMatrix = API::Data::Mat4();
	for (int i = 0; i < 4; i++) // Iteracja po wierszach macierzy wynikowej.
	{
		for (int j = 0; j < 4; j++) // Iteracja po kolumnach macierzy wynikowej.
		{
			float result = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				result += _columns[j][k] * otherMatrix[k][i];
			}
			resultMatrix[j][i] = result;
		}
	}
	return resultMatrix;
}
const float API::Data::Mat4::GetValue(int column, int row) const
{
	assert(column >= 0 && column <= 3 && row >= 0 && row <= 3);
	return _columns[column][row];
}

void API::Data::Mat4::SetValue(int column, int row, float value)
{
	assert(column >= 0 && column <= 3 && row >= 0 && row <= 3);
	_columns[column][row] = value;
}

void API::Data::Mat4::Eye(float value)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				_columns[i][j] = value;
			}
			else
			{
				_columns[i][j] = 0.0f;
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
			_columns[j][i] = rotations[j][i];
		}
	}
	_columns[3][0] = translations.X;
	_columns[3][1] = translations.Y;
	_columns[3][2] = translations.Z;
}


API::Data::Vec4 API::Data::Mat4::operator[](const int& column) const
{
	assert(column >= 0 && column <= 3);
	return _columns[column];
}
API::Data::Vec4& API::Data::Mat4::operator[](const int& column)
{
	assert(column >= 0 && column <= 3);
	return _columns[column];
}
const float* API::Data::Mat4::GetMatrixPointer() const
{
	return &_columns[0].X;
}

