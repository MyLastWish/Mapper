#include "Line.h"
#include <iostream>
Graphic::Graphic3D::Line::Line() : DrawableObject()
{
}

Graphic::Graphic3D::Line::Line(const Graphic::Graphic3D::Line& original) : DrawableObject()
{
}

Graphic::Graphic3D::Line::Line(Graphic::Graphic3D::Infos::LineInfo* info) : DrawableObject()
{
	if (info->Length == 0.0f)
	{
		std::cout << "constructor out" << std::endl;
		return; // TODO: Dodanie wywalania bledu.
	}
	std::cout << "In constructor" << std::endl;
	_position = info->Start.ToVec3();
	_drawAlong(info);
}

Graphic::Graphic3D::Line::~Line() 
{
	std::cout << "In destructor" << std::endl;
}

void Graphic::Graphic3D::Line::_drawAlong(Graphic::Graphic3D::Infos::LineInfo* info)
{
	std::vector<float> coords;
	std::vector<unsigned> indices;
	unsigned iCount = 0;
	unsigned pCount = 0;
	std::vector<API::Data::Vec3> points;
	auto addVec3 = [&points, &indices, &iCount, &pCount](API::Data::Vec3 vec)
	{
		if (points.empty())
		{
			indices.push_back(0);
			points.push_back(vec);
			pCount = 1;
			iCount = 1;
			return;
		}
		bool found = false;
		for (unsigned i = 0; i < iCount; i++)
		{
			if (points[indices[i]] == vec)
			{
				indices.push_back(indices[i]);
				iCount++;
				found = true;
				break;
			}
		}
		if (!found)
		{
			points.push_back(vec);
			indices.push_back(pCount);
			pCount++;
			iCount++;
		}
	};
	auto addTriangle = [&addVec3](API::Data::Vec3& first, API::Data::Vec3& second, API::Data::Vec3& third)
	{
		addVec3(first);
		addVec3(second);
		addVec3(third);
	};
	auto setRectangleFace = [&](Graphic::Graphic3D::Infos::RelativeFaceInfo* info, float height, float width)
	{
		info->LowerLeftCornerTranslation = API::Data::Vec3(info->Center.X, info->Center.Y, info->Center.Z + (width / 2.0f));
		info->LowerRightCornerTranslation = API::Data::Vec3(info->Center.X, info->Center.Y, info->Center.Z - (width / 2.0f));
		info->UpperLeftCornerTranslation = API::Data::Vec3(info->Center.X, info->Center.Y + height, info->Center.Z + (width / 2.0f));
		info->UpperRightCornerTranslation = API::Data::Vec3(info->Center.X, info->Center.Y + height, info->Center.Z - (width / 2.0f));
	};
	auto rotateInfo = [](Graphic::Graphic3D::Infos::RelativeFaceInfo* info, API::Data::Vec3 angles)
	{
		info->LowerLeftCornerTranslation.Rotate(angles);
		info->LowerRightCornerTranslation.Rotate(angles);
		info->UpperLeftCornerTranslation.Rotate(angles);
		info->UpperRightCornerTranslation.Rotate(angles);
	};

	Graphic::Graphic3D::Infos::RelativeFaceInfo* startInfo = new Graphic::Graphic3D::Infos::RelativeFaceInfo();
	Graphic::Graphic3D::Infos::RelativeFaceInfo* endInfo = new Graphic::Graphic3D::Infos::RelativeFaceInfo();
	startInfo->Center = API::Data::Vec3();
	endInfo->Center = API::Data::Vec3();
	setRectangleFace(startInfo, info->Height, info->Width);
	setRectangleFace(endInfo, info->Height, info->Width);
	///
	API::Data::Vec3 startRotations = info->StartFaceNormal.AnglesFrom(info->Length > 0 ? API::Data::Vec3(1.0f, 0.0f, 0.0f) : API::Data::Vec3(-1.0f, 0.0f, 0.0f));
	API::Data::Vec3 endRotations = info->EndFaceNormal.AnglesFrom(info->Length <= 0 ? API::Data::Vec3(1.0f, 0.0f, 0.0f) : API::Data::Vec3(-1.0f, 0.0f, 0.0f));
	///
	rotateInfo(startInfo, startRotations);
	rotateInfo(endInfo, endRotations);
	///
	API::Data::Vec3 translation = API::Data::Vec3(info->Length, 0.0f, 0.0f);
	endInfo->Center.Translate(translation);
	endInfo->LowerLeftCornerTranslation.Translate(translation);
	endInfo->UpperLeftCornerTranslation.Translate(translation);
	endInfo->LowerRightCornerTranslation.Translate(translation);
	endInfo->UpperRightCornerTranslation.Translate(translation);

	// Dodanie poczatku.
	addTriangle(startInfo->LowerRightCornerTranslation, startInfo->LowerLeftCornerTranslation, startInfo->UpperLeftCornerTranslation);
	addTriangle(startInfo->UpperRightCornerTranslation, startInfo->LowerRightCornerTranslation, startInfo->LowerLeftCornerTranslation);
	// Dodanie konca.
	addTriangle(endInfo->UpperLeftCornerTranslation, endInfo->LowerLeftCornerTranslation, endInfo->LowerRightCornerTranslation);
	addTriangle(endInfo->LowerLeftCornerTranslation, endInfo->LowerRightCornerTranslation, endInfo->UpperRightCornerTranslation);
	// Dodanie gory.
	addTriangle(endInfo->UpperRightCornerTranslation, endInfo->UpperLeftCornerTranslation, startInfo->UpperLeftCornerTranslation);
	addTriangle(endInfo->UpperLeftCornerTranslation, startInfo->UpperRightCornerTranslation, startInfo->UpperLeftCornerTranslation);
	// Dodanie dolu.
	addTriangle(endInfo->LowerRightCornerTranslation, startInfo->LowerLeftCornerTranslation, startInfo->LowerRightCornerTranslation);
	addTriangle(endInfo->LowerRightCornerTranslation, startInfo->LowerRightCornerTranslation, endInfo->LowerLeftCornerTranslation);
	// Dodanie przodu.
	addTriangle(endInfo->UpperRightCornerTranslation, startInfo->UpperLeftCornerTranslation, startInfo->LowerLeftCornerTranslation);
	addTriangle(endInfo->UpperRightCornerTranslation, startInfo->LowerLeftCornerTranslation, endInfo->LowerRightCornerTranslation);
	// Dodanie tylu.
	addTriangle(endInfo->UpperLeftCornerTranslation, startInfo->LowerLeftCornerTranslation, startInfo->UpperLeftCornerTranslation);
	addTriangle(endInfo->LowerLeftCornerTranslation, startInfo->LowerRightCornerTranslation, endInfo->UpperRightCornerTranslation);
	for (unsigned i = 0; i < pCount; i++)
	{
		_coords.push_back(points[i].X);
		_coords.push_back(points[i].Y);
		_coords.push_back(points[i].Z);
	}
	for (int i = 0; i < iCount; i++)
	{
		_coords[3 * i] /= 400.0f;
		_coords[(3 * i) + 1] /= 300.0f;
	}
	_position.X /=400.0f;
	_position.Y /=300.0f;
	_indices = indices;
	_indexCount = iCount;
	_coordCount = pCount * 3u;
}

Graphic::Graphic3D::Infos::RelativeFaceInfo Graphic::Graphic3D::Line::_getEndFaceInfo(API::Data::Vec3 section, API::Data::Vec3 normal, float thickness, float width)
{
	Graphic::Graphic3D::Infos::RelativeFaceInfo info;
	auto dotProduct = [](API::Data::Vec3 first, API::Data::Vec3 second) -> API::Data::Vec3
	{
		return API::Data::Vec3(first.Y * second.Z - first.Z * second.Y, first.Z * second.X - first.X * second.Z, first.X * second.Y - first.Y * second.X);
	};
	auto scaleToLength = [](API::Data::Vec3 vector, float desiredLength) -> API::Data::Vec3
	{
		float factor = desiredLength / vector.GetLength();
		return API::Data::Vec3(vector.X * factor, vector.Y * factor, vector.Z * factor);
	};
	info.LowerLeftCornerTranslation = scaleToLength(dotProduct(normal, section), width / 2.0f);
	info.LowerRightCornerTranslation = scaleToLength(dotProduct(section, normal), width / 2.0f);
	info.UpperLeftCornerTranslation = API::Data::Vec3(info.LowerLeftCornerTranslation.X, info.LowerLeftCornerTranslation.Y + thickness, info.LowerLeftCornerTranslation.Z);
	info.UpperRightCornerTranslation = API::Data::Vec3(info.LowerRightCornerTranslation.X, info.LowerRightCornerTranslation.Y + thickness, info.LowerRightCornerTranslation.Z);
	return info;
}

void Graphic::Graphic3D::copyLines(Line* from, Line* to)
{
	to->_color = from->_color;
	to->_coordCount = from->_coordCount;
	to->_coords = from->_coords;
	to->_indexCount = from->_indexCount;
	to->_indices = from->_indices;
	to->_normals = from->_normals;
	to->_position = from->_position;
	to->_rotation = from->_rotation;
	to->_readyToDraw = false;
}