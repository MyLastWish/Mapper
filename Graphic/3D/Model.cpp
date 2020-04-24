#include "Model.h"
Graphic::Graphic3D::Model::Model() : DrawableContainer()
{
}

Graphic::Graphic3D::Model::Model(std::vector<DrawableObject*> vec, unsigned count) : DrawableContainer(vec, count)
{
}

Graphic::Graphic3D::Model::Model(Mesh mesh) : DrawableContainer(std::vector<DrawableObject*>{new Mesh(mesh)}, 1u)
{
}

void Graphic::Graphic3D::Model::Load(const char* path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
    {
        return; // TODO: wywalanie bledu.
    }
}

void Graphic::Graphic3D::Model::_aiNodeToMeshes(aiNode* node, const aiScene* scene)
{
    for (unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->Add(new Mesh(mesh, scene));
    }
    for (unsigned i = 0; i < node->mNumChildren; i++)
    {
        _aiNodeToMeshes(node->mChildren[i], scene);
    }
}