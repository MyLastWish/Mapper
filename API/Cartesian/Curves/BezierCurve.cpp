#include "BezierCurve.h"
API::Cartesian::Curves::BezierCurve::BezierCurve()
{
	API::Cartesian::Point2D<float> zeroPoint = API::Cartesian::Point2D<float>(0.0f, 0.0f);
	_setPoints(zeroPoint, zeroPoint, zeroPoint, zeroPoint);
}

API::Cartesian::Curves::BezierCurve::BezierCurve(API::Cartesian::Point2D<float> start, API::Cartesian::Point2D<float> fCP, API::Cartesian::Point2D<float> sCP, API::Cartesian::Point2D<float> end)
{
	API::Cartesian::Point2D<float> zeroPoint = API::Cartesian::Point2D<float>(0.0f, 0.0f);
	_setPoints(start, fCP, sCP, end);
}

void API::Cartesian::Curves::BezierCurve::_setPoints(API::Cartesian::Point2D<float> start, API::Cartesian::Point2D<float> fCP, API::Cartesian::Point2D<float> sCP, API::Cartesian::Point2D<float> end)
{
	_start = start;
	_firstControlPoint = fCP;
	_secondControlPoint = sCP;
	_end = end;
}

API::Cartesian::Point2D<float>* API::Cartesian::Curves::BezierCurve::Subdivide(float minimalLength, unsigned* count)
{
	unsigned counter = 1;
	API::Cartesian::Point2D<float>* results;
	std::vector<API::Cartesian::Curves::BezierCurve> curves;
	curves.push_back(*this);
	API::Cartesian::Curves::BezierCurve* subdivisonResults = DivideInTwo(minimalLength);
	bool completed = true;
	do
	{
		std::vector<API::Cartesian::Curves::BezierCurve> curvesToBeAdded;
		unsigned toBeAddedCount = 0;
		for (int i = 0; i < curves.size(); i++)
		{
			if (subdivisonResults == nullptr)
			{
				completed &= true;
				continue;
			}
			else
			{
				completed &= false;
				curvesToBeAdded.push_back(*subdivisonResults);
				curvesToBeAdded.push_back(subdivisonResults[1]);
			}
		}
		for (unsigned i = 0; i < toBeAddedCount; i++)
		{
			counter++;
			curves.push_back(curvesToBeAdded[i]);
		}
	} while (!completed);
	results = (API::Cartesian::Point2D<float>*)malloc(counter * sizeof(API::Cartesian::Point2D<float>) + 1);
	results[0] = curves[0].GetStart();
	for (unsigned i = 0; i < counter; i++)
	{
		results[i + 1] = curves[i].GetEnd();
	}
	*count = counter;
	return results;
}

API::Cartesian::Point2D<float> API::Cartesian::Curves::BezierCurve::GetStart() const
{
	return _start;
}

API::Cartesian::Point2D<float> API::Cartesian::Curves::BezierCurve::GetEnd() const
{
	return _end;
}