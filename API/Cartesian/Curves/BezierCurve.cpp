#include "BezierCurve.h"
API::Cartesian::Curves::BezierCurve::BezierCurve()
{
	API::Cartesian::Point2D zeroPoint = API::Cartesian::Point2D(0.0f, 0.0f);
	_setPoints(zeroPoint, zeroPoint, zeroPoint, zeroPoint);
}

API::Cartesian::Curves::BezierCurve::BezierCurve(API::Cartesian::Point2D start, API::Cartesian::Point2D fCP, API::Cartesian::Point2D sCP, API::Cartesian::Point2D end)
{
	API::Cartesian::Point2D zeroPoint = API::Cartesian::Point2D(0.0f, 0.0f);
	_setPoints(start, fCP, sCP, end);
}

void API::Cartesian::Curves::BezierCurve::_setPoints(API::Cartesian::Point2D start, API::Cartesian::Point2D fCP, API::Cartesian::Point2D sCP, API::Cartesian::Point2D end)
{
	_start = start;
	_firstControlPoint = fCP;
	_secondControlPoint = sCP;
	_end = end;
}

std::vector<API::Cartesian::Point2D*> API::Cartesian::Curves::BezierCurve::Subdivide(float minimalLength, unsigned* count)
{
	std::vector<API::Cartesian::Point2D*> results;
	std::vector<API::Cartesian::Curves::BezierCurve*> curves;
	curves.push_back(this);
	unsigned counter = 1;
	bool completed;
	do
	{
		completed = true;
		std::vector<API::Cartesian::Curves::BezierCurve*> curvesToBeAdded;
		unsigned toBeAddedCount = 0;
		for (int i = 0; i < counter; i++)
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
				toBeAddedCount += 2;
			}
		}
		for (unsigned i = 0; i < toBeAddedCount; i++)
		{
			counter++;
			curves.push_back(curvesToBeAdded[i]);
		}
	} while (!completed);
	results.push_back(new API::Cartesian::Point2D(curves[0]->GetStart()));
	for (unsigned i = 0; i < counter; i++)
	{
		results.push_back(new API::Cartesian::Point2D(curves[i]->GetEnd()));
	}
	*count = counter;
	return results;
}

API::Cartesian::Point2D API::Cartesian::Curves::BezierCurve::GetStart() const
{
	return _start;
}

API::Cartesian::Point2D API::Cartesian::Curves::BezierCurve::GetEnd() const
{
	return _end;
}

API::Cartesian::Curves::BezierCurve** API::Cartesian::Curves::BezierCurve::DivideInTwo(float minimalLength)
{
	if (_valueInToleranceRangeFrom((this->_firstControlPoint.GetX() - this->_start.GetX()) / (this->_start.GetX() - this->_end.GetX()), minimalLength, (this->_firstControlPoint.GetY() - this->_start.GetY()) / (this->_start.GetY() - this->_end.GetY()))
		&& _valueInToleranceRangeFrom((this->_secondControlPoint.GetX() - this->_start.GetX()) / (this->_start.GetX() - this->_end.GetX()), minimalLength, (this->_secondControlPoint.GetY() - this->_start.GetY()) / (this->_start.GetY() - this->_end.GetY())))
	{
		return nullptr;
	}

	API::Cartesian::Point2D midStartFirstCP, midFirstCPSecondCP, midSecondCPEnd, midStartSide, midEndSide, midOverall;
	midStartFirstCP = API::Cartesian::Point2D((this->_start.GetX() + this->_firstControlPoint.GetX()) / 2.0f, (this->_start.GetY() + this->_firstControlPoint.GetY()) / 2.0f);
	midFirstCPSecondCP = API::Cartesian::Point2D((this->_firstControlPoint.GetX() + this->_secondControlPoint.GetX()) / 2.0f, (this->_firstControlPoint.GetY() + this->_secondControlPoint.GetY()) / 2.0f);
	midSecondCPEnd = API::Cartesian::Point2D((this->_secondControlPoint.GetX() + this->_end.GetX()) / 2.0f, (this->_secondControlPoint.GetY() + this->_end.GetY()) / 2.0f);

	midStartSide = API::Cartesian::Point2D((midStartFirstCP.GetX() + midFirstCPSecondCP.GetX()) / 2.0f, (midStartFirstCP.GetY() + midFirstCPSecondCP.GetY()) / 2.0f);
	midEndSide = API::Cartesian::Point2D((midFirstCPSecondCP.GetX() + midSecondCPEnd.GetX()) / 2.0f, (midFirstCPSecondCP.GetY() + midSecondCPEnd.GetY()) / 2.0f);
	midOverall = API::Cartesian::Point2D((midStartSide.GetX() + midEndSide.GetX()) / 2.0f, (midStartSide.GetY() + midEndSide.GetY()) / 2.0f);

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

float API::Cartesian::Curves::BezierCurve::_distanceToPoint(API::Cartesian::Point2D point)
{
	API::Cartesian::Vector2D startToPoint, shortestVector, startToEndVector;
	startToPoint = API::Cartesian::Vector2D(_start, point);
	startToEndVector = API::Cartesian::Vector2D(_start, _end);
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
bool API::Cartesian::Curves::BezierCurve::_valueInToleranceRangeFrom(float value, float tolerance, float reference)
{
	if (value != value)
	{
		value = 0.0f;
	}
	if (tolerance != tolerance)
	{
		tolerance = 0.0f;
	}
	if (reference != reference)
	{
		reference = 0.0f;
	}
	float upper, lower;
	upper = reference + tolerance;
	lower = reference - tolerance;
	return (value - upper) * (value - lower) <= 0;
}