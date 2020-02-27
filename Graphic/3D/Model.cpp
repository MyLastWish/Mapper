#include "Model.h"
Graphic::Graphic3D::Model::Model() : DrawableContainer<Mesh>()
{
}

Graphic::Graphic3D::Model::Model(std::vector<Mesh*> vec, unsigned count) : DrawableContainer<Mesh>(vec, count)
{
}

Graphic::Graphic3D::Model::Model(Mesh mesh) : DrawableContainer<Mesh>(std::vector<Mesh*>{new Mesh(mesh)}, 1u)
{
}