#include "Mesh.h"
Graphic::Graphic3D::Mesh::Mesh(aiMesh* mesh, const aiScene* scene) : Drawable()
{
	std::vector<float> points;
	std::vector<unsigned> indices;
	std::vector<API::Cartesian::Vector3D> normals;

	for (unsigned i = 0; i < mesh->mNumVertices; i++)
	{
		// przetwarzanie wierzcholkow
		points.push_back(mesh->mVertices[i].x);
		points.push_back(mesh->mVertices[i].y);
		points.push_back(mesh->mVertices[i].z);
		normals.push_back(API::Cartesian::Vector3D(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		_coordCount += 3;
	}
	// przetwarzanie indeksow
	for (unsigned i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
			_indexCount++; // W innych konstruktorach zliczanie indeksow istnieje!
		}
	}
	_coords = points;
	_indices = indices;
	_normals = normals;
}

Graphic::Graphic3D::Mesh::Mesh(std::vector<API::Cartesian::Point2D*> points, std::vector<unsigned> indices) : Drawable(points, indices)
{
	_normals.clear();
	for (int i = 0; i < _indexCount; i++)
	{
		_normals.push_back(API::Cartesian::Vector3D(0.0f, 0.0f, 1.0f));
	}
}

Graphic::Graphic3D::Mesh::Mesh(std::vector<API::Cartesian::Point3D*> points, std::vector<unsigned> indices, std::vector<API::Cartesian::Vector3D> normals) : Drawable(points, indices, normals)
{
}
void Graphic::Graphic3D::Mesh::_prepare()
{
	for (unsigned i = 0; i < _coordCount; i += 3)
	{
		_coords[i] = (_coords[i] / 400.0f);
		_coords[(int)i + 1] = (_coords[(int)i + 1u] / 300.0f);
	}
}