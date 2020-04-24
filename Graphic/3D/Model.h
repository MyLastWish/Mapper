#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include "DrawableContainer.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Graphic
{
	namespace Graphic3D
	{
		class Model : public DrawableContainer
		{
		private:
			void _aiNodeToMeshes(aiNode*, const aiScene*);
		public:
			Model();
			Model(std::vector<DrawableObject*>, unsigned);
			Model(Mesh);
			void Load(const char*);
		};
	}
}

#endif