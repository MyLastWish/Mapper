#include "Line.h"
Graphic::Graphic3D::Line::Line() : Drawable<float>()
{
}

std::vector<float> Graphic::Graphic3D::Line::_drawAlong(Graphic::Graphic3D::Infos::LineInfo* info, float thickness)
{
	std::vector<float> coords;
	API::Cartesian::Vector3D<float> mainVector = API::Cartesian::Vector3D<float>(info->Start, info->End);
	std::vector<API::Cartesian::Point3D<float>> points;
	// Wyznaczenie punktow podstawy dolnej.
	API::Cartesian::Vector3D<float>* startShift = info->StartFaceNormal.FindPerpendicular(info->LineNormal);
	API::Cartesian::Vector3D<float>* endShift = info->EndFaceNormal.FindPerpendicular(info->LineNormal);
	points.push_back(info->Start.GetMovedCopy(startShift));
	points.push_back(info->Start.GetMovedCopy(startShift->GetInvertedCopy()));
	points.push_back(info->End.GetMovedCopy(endShift->GetInvertedCopy()));
	points.push_back(info->End.GetMovedCopy(endShift->GetInvertedCopy()));
	//API::Cartesian::Point3D<float>* startUpperPoint = info->Start.GetMovedCopy(Findper)
}