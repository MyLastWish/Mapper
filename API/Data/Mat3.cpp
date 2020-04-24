#include "Mat3.h"
#include "Vec3.h"
#include <iostream>
API::Data::Mat3::Mat3(float value)
{
	_columns = new API::Data::Vec3[3];
	assert(_columns != 0);

	
	for (int i = 0; i < 3; i++)
	{
		_columns[i] = API::Data::Vec3();
		_columns[i].X = value;
		_columns[i].Y = value;
		_columns[i].Z = value;

	}
}

API::Data::Mat3::Mat3() : API::Data::Mat3(0.0f)
{
}

API::Data::Mat3::~Mat3()
{
	std::cout << "Attempting to destroy Mat3 " << this << std::endl;
	std::cout << _columns << std::endl;
	if(_columns == nullptr)
	{
		return;
	}
	delete[] _columns;
	std::cout << "Destroyed" << std::endl;
}

API::Data::Mat3::Mat3(const API::Data::Mat3& original) : API::Data::Mat3(0.0f)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_columns[i][j]= original[i][j];
		}
	}
}

API::Data::Vec3 API::Data::Mat3::operator*(const API::Data::Vec3& vector)
{
	API::Data::Vec3 result = API::Data::Vec3();
	result.X = _columns[0].X * vector.X + _columns[1].X * vector.Y + _columns[2].X * vector.Z;
	result.Z = _columns[0].Y * vector.X + _columns[1].Y * vector.Y + _columns[2].Y * vector.Z;
	result.Y = _columns[0].Z * vector.X + _columns[1].Z * vector.Y + _columns[2].Z * vector.Z;
	return result;
}

API::Data::Mat3 API::Data::Mat3::operator*(const API::Data::Mat3& otherMatrix)
{
	API::Data::Mat3 resultMatrix = API::Data::Mat3();
	for (int i = 0; i < 3; i++) // Iteracja po wierszach macierzy wynikowej.
	{
		for (int j = 0; j < 3; j++) // Iteracja po kolumnach macierzy wynikowej.
		{
			float result = 0.0f;
			for (int k = 0; k < 3; k++)
			{
				result += _columns[j][k] * otherMatrix[k][i];
			}
			resultMatrix[j][i] = result;
		}
	}
	return resultMatrix;
}


API::Data::Vec3& API::Data::Mat3::operator[](const int& column)
{
	assert(column >= 0 && column <= 3);
	return _columns[column];
}
API::Data::Vec3 API::Data::Mat3::operator[](const int& column) const
{
	assert(column >= 0 && column <= 3);
	return _columns[column];
}

API::Data::Mat3& API::Data::Mat3::operator=(const Mat3& original)
{
	if(&original == this)
	{
		return *this;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_columns[i][j]= original[i][j];
		}
	}
	return *this;
}
const float API::Data::Mat3::GetValue(int column, int row) const
{
	assert(row <= 2 && row >= 0 && column <= 2 && column >= 0);
	return _columns[column][row];
}

void API::Data::Mat3::SetValue(int column, int row, float value)
{
	assert(row <= 2 && row >= 0 && column <= 2 && column >= 0);
	_columns[column][row] = value;
}

void API::Data::Mat3::Eye(float value)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
			{
				_columns[j][i] = value;
			}
			else
			{
				_columns[j][i] = 0.0f;
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