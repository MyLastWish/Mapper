#include "Path.h"
#include <iostream>
SVG::Data::Path::Path()
{
	_indices.clear();
	_points.clear();
}
SVG::Data::Path::Path(NSVGpath* originalPath)
{
	if (originalPath == nullptr)
	{
		return;
	}
	_indices.clear();
	_points.clear();

	API::Cartesian::Point2D* points = 0;
	for (int i = 0; i < originalPath->npts - 1; i += 3)
	{
		float* points = &(originalPath->pts[i * 2]);
		API::Cartesian::Curves::BezierCurve curve = API::Cartesian::Curves::BezierCurve(
			API::Cartesian::Point2D(points[0], points[1]),
			API::Cartesian::Point2D(points[2], points[3]),
			API::Cartesian::Point2D(points[4], points[5]),
			API::Cartesian::Point2D(points[6], points[7]));
		unsigned resultCount = 0;
		std::vector<API::Cartesian::Point2D*> resultPoints = curve.Subdivide(1.0f, &resultCount);
		for (unsigned j = 0; j < resultCount; j++)
		{
			_addPointAndIndex(resultPoints[j]);
		}
	}
}

void SVG::Data::Path::_addPointAndIndex(API::Cartesian::Point2D* point)
{
	if (_indices.empty() || _points.empty() || _indexCount == 0 || _pointCount == 0)
	{
		_indices.clear();
		_indices.push_back(0);
		_indexCount = 1;
		_points.clear();
		_points.push_back(point);
		_pointCount = 1;
		return;
	}
	for (unsigned i = 0; i < _indexCount; i++)
	{
		if (_points[_indices[i]] == point)
		{
			_indices.push_back(i);
			_indexCount++;
			return;
		}
	}
	_indices.push_back(_indexCount++);
	_points.push_back(point);
	_pointCount++;
}
std::vector<Graphic::Graphic3D::Line*> SVG::Data::Path::ToLines(float width, unsigned& count)
{
	std::vector<Graphic::Graphic3D::Line*> result;
	std::cout << "New Info" << std::endl;
	Graphic::Graphic3D::Infos::LineInfo* info = new Graphic::Graphic3D::Infos::LineInfo();
	info->Height = width;
	info->Width = width;
	API::Data::Vec3 rotation = API::Data::Vec3();
	API::Data::Vec3 referenceVec = API::Data::Vec3(-1.0f, 0.0f, 0.0f);
	API::Cartesian::Vector3D sectionVector, previousVector, nextVector;
	for (unsigned i = 0; i < _indexCount; i++)
	{
		std::cout << "Run no: " << i << std::endl;
		if (i == 0)
		{
			sectionVector = API::Cartesian::Vector3D(
				API::Cartesian::Point3D(
					_points[_indices[_indexCount - 1u]]->GetX(),
					_points[_indices[_indexCount - 1u]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f));
			previousVector = API::Cartesian::Vector3D( // UWAGA! moze wstapic blad jezeli jest mniej niz 3 pkt w sciezce.
				API::Cartesian::Point3D(
					_points[_indices[_indexCount - 2u]]->GetX(),
					_points[_indices[_indexCount - 2u]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[_indexCount - 1u]]->GetX(),
					_points[_indices[_indexCount - 1u]]->GetY(),
					0.0f));
			nextVector = API::Cartesian::Vector3D(
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[i + 1u]]->GetX(),
					_points[_indices[i + 1u]]->GetY(),
					0.0f));
		}
		else if (i == _indexCount - 1)
		{
			sectionVector = API::Cartesian::Vector3D(
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[0]]->GetX(),
					_points[_indices[0]]->GetY(),
					0.0f));
			previousVector = API::Cartesian::Vector3D( // UWAGA! moze wstapic blad jezeli jest mniej niz 3 pkt w sciezce.
				API::Cartesian::Point3D(
					_points[_indices[i - 1u]]->GetX(),
					_points[_indices[i - 1u]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f));
			nextVector = API::Cartesian::Vector3D(
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[0]]->GetX(),
					_points[_indices[0]]->GetY(),
					0.0f));
		}
		else
		{
			sectionVector = API::Cartesian::Vector3D(
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[i + 1u]]->GetX(),
					_points[_indices[i + 1u]]->GetY(),
					0.0f));
			previousVector = API::Cartesian::Vector3D( // UWAGA! moze wstapic blad jezeli jest mniej niz 3 pkt w sciezce.
				API::Cartesian::Point3D(
					_points[_indices[i - 1u]]->GetX(),
					_points[_indices[i - 1u]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f));
			nextVector = API::Cartesian::Vector3D(
				API::Cartesian::Point3D(
					_points[_indices[i]]->GetX(),
					_points[_indices[i]]->GetY(),
					0.0f),
				API::Cartesian::Point3D(
					_points[_indices[i + 1u]]->GetX(),
					_points[_indices[i + 1u]]->GetY(),
					0.0f));
		}
		API::Data::Vec3 current = sectionVector.GetVectorCoords();
		API::Data::Vec3 next = nextVector.GetVectorCoords();
		API::Data::Vec3 previous = previousVector.GetVectorCoords();
		info->EndFaceNormal = API::Data::Vec3(-1.0f, 0.0f, 0.0f);
		info->EndFaceNormal.Rotate(next.AnglesFrom(current));
		info->StartFaceNormal = API::Data::Vec3(1.0f, 0.0f, 0.0f);
		info->StartFaceNormal.Rotate(current.AnglesFrom(previous));
		info->Start = sectionVector.GetStart();
		info->Length = sectionVector.GetLength();
		if(info->Length == 0.0f)
		{
			continue;
		}
		std::cout << "X: " << info->Width  << std::endl;

		std::cout << "New Line" << std::endl;
		Graphic::Graphic3D::Line* line = new Graphic::Graphic3D::Line(info);
		line->SetRotation(current.AnglesFrom(referenceVec));
		result.push_back(line);
		count++;
	}
	return result;
}