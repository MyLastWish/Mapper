#include "Line.h"
Graphic::Graphic3D::Line::Line() : Drawable()
{
}

Graphic::Graphic3D::Line::Line(API::Cartesian::Point3D start, float length, float thickness) : Drawable() // TODO: Zmienic sposob rysowania bo jest zbyt zamotany - ma byc staly i modyfikowany macierzami.
{
	Graphic::Graphic3D::Infos::LineInfo* info = new Graphic::Graphic3D::Infos::LineInfo();
	info->Start = start;
	info->EndFaceNormal = start;
	info->StartFaceNormal = start;
	_drawAlong(info, 10, 10);
}

void Graphic::Graphic3D::Line::_drawAlong(Graphic::Graphic3D::Infos::LineInfo* info, float thickness, float width) // TODO: poprawic konsystencje funkcji.
{
	std::vector<float> coords;
	std::vector<unsigned> indices;
	unsigned iCount = 0;
	unsigned pCount = 0;
	std::vector<API::Data::Vec3> points;
	auto addVec3 = [&points, &indices, &iCount, &pCount](API::Data::Vec3 vec)
	{
		bool found = false;
		for (unsigned i = 0; i < iCount; i++)
		{
			if (points[indices[i]] == vec)
			{
				indices.push_back(i);
				iCount++;
				found = true;
				break;
			}
		}
		if (!found)
		{
			indices.push_back(pCount++);
			iCount++;
		}
	};
	auto addTriangle = [&addVec3](API::Data::Vec3& first, API::Data::Vec3& second, API::Data::Vec3& third)
	{
		addVec3(first);
		addVec3(second);
		addVec3(third);
	};
	auto rebase = [](API::Data::Vec3& vec, API::Cartesian::Point3D oldPoint, API::Cartesian::Point3D newPoint)
	{
		API::Data::Vec3 oldPosition = oldPoint.GetMovedCopy(vec).ToVec3();
		return API::Data::Vec3(oldPosition.X - newPoint.GetX(), oldPosition.Y - newPoint.GetY(), oldPosition.Z - newPoint.GetZ());
	};
	auto rebaseInfoToObjectCentre = [&rebase](Graphic::Graphic3D::Infos::RelativeFaceInfo& info)
	{
		rebase(info.LowerLeftCornerTranslation, info.CenterOfBase, API::Cartesian::Point3D());
		rebase(info.LowerRightCornerTranslation, info.CenterOfBase, API::Cartesian::Point3D());
		rebase(info.UpperLeftCornerTranslation, info.CenterOfBase, API::Cartesian::Point3D());
		rebase(info.UpperRightCornerTranslation, info.CenterOfBase, API::Cartesian::Point3D());
		info.CenterOfBase = API::Cartesian::Point3D();
	};
	API::Cartesian::Vector3D mainVector = API::Cartesian::Vector3D(info->Start, info->End);
	Graphic::Graphic3D::Infos::RelativeFaceInfo startInfo = _getEndFaceInfo(mainVector.GetVectorCoords(), mainVector.GetInvertedCopy().GetVectorCoords(), thickness, width);
	Graphic::Graphic3D::Infos::RelativeFaceInfo endInfo = _getEndFaceInfo(mainVector.GetInvertedCopy().GetVectorCoords(), mainVector.GetVectorCoords(), thickness, width);
	rebaseInfoToObjectCentre(startInfo);
	rebaseInfoToObjectCentre(endInfo);

	// Dodanie poczatku.
	addTriangle(startInfo.LowerRightCornerTranslation, startInfo.LowerLeftCornerTranslation, startInfo.UpperLeftCornerTranslation);
	addTriangle(startInfo.UpperRightCornerTranslation, startInfo.LowerRightCornerTranslation, startInfo.LowerLeftCornerTranslation);
	// Dodanie konca.
	addTriangle(endInfo.LowerRightCornerTranslation, endInfo.LowerLeftCornerTranslation, endInfo.UpperLeftCornerTranslation);
	addTriangle(endInfo.UpperRightCornerTranslation, endInfo.LowerRightCornerTranslation, endInfo.LowerLeftCornerTranslation);
	// Dodanie gory.
	addTriangle(endInfo.UpperRightCornerTranslation, endInfo.UpperLeftCornerTranslation, startInfo.UpperLeftCornerTranslation);
	addTriangle(endInfo.UpperLeftCornerTranslation, startInfo.UpperRightCornerTranslation, startInfo.UpperLeftCornerTranslation);
	// Dodanie dolu.
	addTriangle(endInfo.LowerRightCornerTranslation, startInfo.LowerLeftCornerTranslation, startInfo.LowerRightCornerTranslation);
	addTriangle(endInfo.LowerRightCornerTranslation, startInfo.LowerRightCornerTranslation, endInfo.LowerLeftCornerTranslation);
	// Dodanie przodu.
	addTriangle(endInfo.UpperRightCornerTranslation, startInfo.UpperLeftCornerTranslation, startInfo.LowerLeftCornerTranslation);
	addTriangle(endInfo.UpperRightCornerTranslation, startInfo.LowerLeftCornerTranslation, endInfo.LowerRightCornerTranslation);
	// Dodanie tylu.
	addTriangle(endInfo.UpperLeftCornerTranslation, startInfo.LowerLeftCornerTranslation, startInfo.UpperLeftCornerTranslation);
	addTriangle(endInfo.LowerLeftCornerTranslation, startInfo.LowerRightCornerTranslation, endInfo.UpperRightCornerTranslation);
	for (unsigned i = 0; i < pCount; i++)
	{
		_coords.push_back(points[i].X);
		_coords.push_back(points[i].Y);
		_coords.push_back(points[i].Z);
	}
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