#include "Scene.h"

Graphic::Graphic3D::Scene::Scene(Graphic::Graphic3D::Camera* cam, Graphic::Shader* shader) : _camera(cam), _shader(shader)
{
}

void Graphic::Graphic3D::Scene::Add(std::vector<Graphic::Graphic3D::Drawable*> vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == nullptr)
        {
            continue;
        }
        Add(vec[i]);
    }
}

void Graphic::Graphic3D::Scene::Add(Graphic::Graphic3D::Drawable* ptr)
{
    if(ptr == nullptr)
    {
        return;
    }
    _drawables.push_back(ptr);
    _drawableCount++;
}

void Graphic::Graphic3D::Scene::Redraw()
{
    for(unsigned i = 0; i < _drawableCount; i++)
    {
        _drawables[i]->Draw(_shader);
    }
}

void Graphic::Graphic3D::Scene::SetShader(Graphic::Shader* newPtr)
{
    if(newPtr == nullptr)
    {
        return;
    }
    _shader = newPtr;
}

Graphic::Shader* Graphic::Graphic3D::Scene::GetShaderPtr() const
{
    return _shader;
}