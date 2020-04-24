#include "DrawableContainer.h"

Graphic::Graphic3D::DrawableContainer::DrawableContainer(): Drawable()
{
    _contents.clear();
    _count = 0;
}
Graphic::Graphic3D::DrawableContainer::DrawableContainer(std::vector<Graphic::Graphic3D::DrawableObject> vec, unsigned count) : DrawableContainer()
{
    for (int i = 0; i < count; i++)
    {
        Add(new Graphic::Graphic3D::DrawableObject(vec[i]));
    }
}
Graphic::Graphic3D::DrawableContainer::DrawableContainer(std::vector<Graphic::Graphic3D::DrawableObject*> vec, unsigned count) : DrawableContainer()
{
    for (int i = 0; i < count; i++)
    {
        Add(vec[i]);
    }
}
void Graphic::Graphic3D::DrawableContainer::_drawObject(Shader* shader)
{
    for (int i = 0; i < _count; i++)
    {
        Graphic::Graphic3D::Drawable* obj = (Graphic::Graphic3D::Drawable*)_contents[i];
        obj->Draw(shader);
    }
}
void Graphic::Graphic3D::DrawableContainer::Add(Graphic::Graphic3D::DrawableObject* element)
{
    _contents.push_back(element);
    _count++;
}

void Graphic::Graphic3D::DrawableContainer::Remove(unsigned index)
{
    if (index == _count - 1)
    {
        _contents.pop_back();
        return;
    }
    for (int i = index; i < _count - 1; i++)
    {
        _contents[i] = _contents[i + 1];
    }
    _contents.pop_back();
}

unsigned Graphic::Graphic3D::DrawableContainer::GetCount() const
{
    return _count;
}

Graphic::Graphic3D::DrawableObject* Graphic::Graphic3D::DrawableContainer::At(unsigned index)
{
    if(index < 0 || index >= _count)
    {
        return nullptr;
    }
    return _contents[index];
}