#include "Mat3.h"
API::Data::Mat3::Mat3(float value)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_matrix[i * 3 + j] = value;
		}
	}
}

API::Data::Mat3::Mat3() :API::Data::Mat3(0.0f)
{
}

API::Data::Mat3::Mat3(const API::Data::Mat3& original) : API::Data::Mat3(0.0f)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_matrix[i * 3 + j] = original.GetValue(i, j);
		}
	}
}

API::Data::Vec3& API::Data::Mat3::operator*(const API::Data::Vec3& vector)
{
	API::Data::Vec3 result = API::Data::Vec3();
	result.X = _matrix[0] * vector.X + _matrix[1] * vector.Y + _matrix[2] * vector.Z;
	result.Y = _matrix[3] * vector.X + _matrix[4] * vector.Y + _matrix[5] * vector.Z;
	result.Z = _matrix[6] * vector.X + _matrix[7] * vector.Y + _matrix[8] * vector.Z;
	return result;
}

API::Data::Mat3& API::Data::Mat3::operator*(const API::Data::Mat3& otherMatrix)
{
	API::Data::Mat3 resultMatrix = API::Data::Mat3();
	for (int i = 0; i < 3; i++) // Iteracja po wierszach macierzy wynikowej.
	{
		for (int j = 0; j < 3; j++) // Iteracja po kolumnach macierzy wynikowej.
		{
			float result = 0;
			for (int k = 0; k < 3; k++)
			{
				result += GetValue(i, k) * otherMatrix.GetValue(k, j);
			}
			SetValue(i, j, result);
		}
	}
	return resultMatrix;
}

const float API::Data::Mat3::GetValue(int row, int column) const
{
	if (row > 2 || row < 0 || column > 2 || column < 0)
	{
		return 0; // TODO: Wywalanie bledu.
	}
	return _matrix[row * 3 + column];
}

void API::Data::Mat3::SetValue(int row, int column, float value)
{
	if (row > 2 || row < 0 || column > 2 || column < 0)
	{
		return; // TODO: Wywalanie bledu.
	}
	_matrix[row * 3 + column] = value;
}

void API::Data::Mat3::Eye(float value)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
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

void API::Data::Mat3::XRotation(float angle)
{
	Eye(1.0f);
	SetValue(0, 0, std::cos(angle));
	SetValue(0, 1, -std::sin(angle));
	SetValue(1, 0, std::sin(angle));
	SetValue(1, 1, std::cos(angle));
}

void API::Data::Mat3::YRotation(float angle)
{
	Eye(1.0f);
	SetValue(0, 0, std::cos(angle));
	SetValue(0, 2, std::sin(angle));
	SetValue(2, 0, -std::sin(angle));
	SetValue(2, 2, std::cos(angle));
}

void API::Data::Mat3::ZRotation(float angle)
{
	Eye(1.0f);
	SetValue(1, 1, std::cos(angle));
	SetValue(1, 2, -std::sin(angle));
	SetValue(2, 1, std::sin(angle));
	SetValue(2, 2, std::cos(angle));
}