#ifndef MESH_H
#define MESH_H
#include "Drawable.h"
#include "Cartesian/Point3D.h"
#include "Cartesian/Point2D.h"
#include "Cartesian/Vector3D.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace Graphic
{
	namespace Graphic3D
	{
		class Mesh : public Drawable<float>
		{
		public:
			Mesh(aiMesh*, const aiScene*);
			Mesh(std::vector<API::Cartesian::Point2D<float>*>, std::vector<unsigned>);
			Mesh(std::vector<API::Cartesian::Point3D<float>*>, std::vector<unsigned>, std::vector<API::Cartesian::Vector3D<float>>);
		};
	}
}
#endif // !MESH_H
