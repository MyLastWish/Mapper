#include "Mesh.h"
Graphic::Graphic3D::Mesh::Mesh(aiMesh* mesh, const aiScene* scene) : Drawable()
{
	std::vector<API::Cartesian::Point3D<float>> points;
	std::vector<unsigned> indices;
	std::vector<API::Cartesian::Vector3D<float>> normals;

	for (unsigned i = 0; i < mesh->mNumVertices; i++)
	{
		// przetwarzanie wierzcholkow
		points.push_back(API::Cartesian::Point3D<float>(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		normals.push_back(API::Cartesian::Vector3D<float>(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
	}
	// przetwarzanie indeksow
}

Graphic::Graphic3D::Mesh::Mesh(std::vector<API::Cartesian::Point2D<float>*> points, std::vector<unsigned> indices) : Drawable(points, indices)
{
}

Graphic::Graphic3D::Mesh::Mesh(std::vector<API::Cartesian::Point3D<float>*> points, std::vector<unsigned> indices, std::vector<API::Cartesian::Vector3D<float>> normals) : Drawable(points, indices, normals)
{
}