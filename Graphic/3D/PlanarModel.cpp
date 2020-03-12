#include "PlanarModel.h"
Graphic::Graphic3D::PlanarModel::PlanarModel() : DrawableContainer<Line>()
{
}

Graphic::Graphic3D::PlanarModel::PlanarModel(std::vector<Line*> vec, unsigned count) : DrawableContainer<Line>(vec, count)
{
}
Graphic::Graphic3D::PlanarModel::PlanarModel(Line line) : DrawableContainer<Line>(std::vector<Line>{line}, 1u)
{
}