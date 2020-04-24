#include "PlanarModel.h"
Graphic::Graphic3D::PlanarModel::PlanarModel() : DrawableContainer()
{
}

Graphic::Graphic3D::PlanarModel::PlanarModel(std::vector<DrawableObject*> vec, unsigned count) : DrawableContainer(vec, count)
{
}
Graphic::Graphic3D::PlanarModel::PlanarModel(Line* line) : DrawableContainer()
{
    Add(line);
}