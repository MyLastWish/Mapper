#include "Path.h"
SVG::Data::Path::Path()
{
	_pointCount = 0;
	_indexCount = 0;
	_indices = 0;
	_points = 0;
}
SVG::Data::Path::Path(NSVGpath* originalPath)
{
	if (originalPath == nullptr)
	{
		return;
	}
	_pointCount = 0;
	_indexCount = 0;
	_indices = 0;
	_points = 0;

	API::Cartesian::Point2D<float>* points = 0;
	for (int i = 0; i < originalPath->npts - 1; i += 3)
	{
		float* points = &(originalPath->pts[i * 2]);
		API::Cartesian::Curves::BezierCurve curve = API::Cartesian::Curves::BezierCurve(
			API::Cartesian::Point2D<float>(points[0], points[1]),
			API::Cartesian::Point2D<float>(points[2], points[3]),
			API::Cartesian::Point2D<float>(points[4], points[5]),
			API::Cartesian::Point2D<float>(points[6], points[7]));
		unsigned resultCount = 0;
		API::Cartesian::Point2D<float>* resultPoints = curve.Subdivide(0.2f, &resultCount);
		for (unsigned j = 0; j < resultCount; j++)
		{
			_addPointAndIndex(resultPoints[j]);
		}
		free(resultPoints);
	}
}

void SVG::Data::Path::_addPointAndIndex(API::Cartesian::Point2D<float> point)
{
	if (_indices == nullptr || _points == nullptr)
	{
		_indices = (unsigned*)malloc(sizeof(unsigned));
		_indices[0] = 0;
		_indexCount = 1;
		_points = (API::Cartesian::Point2D<float>*)malloc(sizeof(API::Cartesian::Point2D<float>));
		_points[0] = point;
		_pointCount = 1;
		return;
	}
	for (unsigned i = 0; i < _indexCount; i++)
	{
		if (_points[_indices[i]] == point)
		{
			_indices = (unsigned*)realloc(_indices, ++_indexCount * sizeof(unsigned));
			_indices[_indexCount - 1] = i;
			return;
		}
	}
	_indices = (unsigned*)realloc(_indices, ++_indexCount * sizeof(unsigned));
	_indices[_indexCount - 1] = _pointCount;
	_points = (API::Cartesian::Point2D<float>*)realloc(_points, ++_pointCount * sizeof(API::Cartesian::Point2D<float>));
	_points[_pointCount - 1] = point;
}