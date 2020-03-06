#include "Path.h"
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
Graphic::Graphic3D::Mesh* SVG::Data::Path::ToMesh()
{
	return new Graphic::Graphic3D::Mesh(_points, _indices);
}