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
	std::vector<API::Cartesian::Curves::BezierCurve*> curves;
	curves.push_back(this);
	bool completed = true;
	do
	{
		std::vector<API::Cartesian::Curves::BezierCurve*> curvesToBeAdded;
		unsigned toBeAddedCount = 0;
		for (int i = 0; i < curves.size(); i++)
		{
			API::Cartesian::Curves::BezierCurve** subdivisonResults = curves[i]->DivideInTwo(minimalLength);
			if (subdivisonResults == nullptr)
			{
				completed &= true;
				continue;
			}
			else
			{
				completed &= false;
				curvesToBeAdded.push_back(subdivisonResults[0]);
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
	results[0] = curves[0]->GetStart();
	for (unsigned i = 0; i < counter; i++)
	{
		results[i + 1] = curves[i]->GetEnd();
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

API::Cartesian::Curves::BezierCurve** API::Cartesian::Curves::BezierCurve::DivideInTwo(float minimalLength)
{
	API::Cartesian::Point2D<float> midStartFirstCP, midFirstCPSecondCP, midSecondCPEnd, midStartSide, midEndSide, midOverall;
	midStartFirstCP = API::Cartesian::Point2D<float>((this->_start.GetX() + this->_firstControlPoint.GetX()) / 2.0f, (this->_start.GetY() + this->_firstControlPoint.GetY()) / 2.0f);
	midFirstCPSecondCP = API::Cartesian::Point2D<float>((this->_firstControlPoint.GetX() + this->_secondControlPoint.GetX()) / 2.0f, (this->_firstControlPoint.GetY() + this->_secondControlPoint.GetY()) / 2.0f);
	midSecondCPEnd = API::Cartesian::Point2D<float>((this->_secondControlPoint.GetX() + this->_end.GetX()) / 2.0f, (this->_secondControlPoint.GetY() + this->_end.GetY()) / 2.0f);

	midStartSide = API::Cartesian::Point2D<float>((midStartFirstCP.GetX() + midFirstCPSecondCP.GetX()) / 2.0f, (midStartFirstCP.GetY() + midFirstCPSecondCP.GetY()) / 2.0f);
	midEndSide = API::Cartesian::Point2D<float>((midFirstCPSecondCP.GetX() + midSecondCPEnd.GetX()) / 2.0f, (midFirstCPSecondCP.GetY() + midSecondCPEnd.GetY()) / 2.0f);
	midOverall = API::Cartesian::Point2D<float>((midStartSide.GetX() + midEndSide.GetX()) / 2.0f, (midStartSide.GetY() + midEndSide.GetY()) / 2.0f);

	if (_distanceToPoint(midOverall) > minimalLength)
	{
		BezierCurve** result = (BezierCurve**)malloc(2 * sizeof(BezierCurve*));
		result[0] = new BezierCurve(_start, midStartFirstCP, midStartSide, midOverall);
		result[1] = new BezierCurve(midOverall, midEndSide, midSecondCPEnd, _end);
		return result;
	}
	else
	{
		return nullptr;
	}
}

float API::Cartesian::Curves::BezierCurve::_distanceToPoint(API::Cartesian::Point2D<float> point)
{
	API::Cartesian::Vector2D<float> startToPoint, shortestVector, startToEndVector;
	startToPoint = API::Cartesian::Vector2D<float>(_start, point);
	startToEndVector = API::Cartesian::Vector2D<float>(_start, _end);
	float ratio = -1;
	if (startToEndVector.GetLength() > 0)
	{
		ratio = startToEndVector.DotProduct(startToPoint) / startToPoint.GetLength();
	}
	if (ratio < 0)
	{
		ratio = 0;
	}
	else if (ratio > 1)
	{
		ratio = 1;
	}
	shortestVector.SetCoords2D(_start.GetX() + ratio * startToEndVector.GetX() - point.GetX(), _start.GetY() + ratio * startToEndVector.GetY() - point.GetY());
	return shortestVector.GetLength();
}