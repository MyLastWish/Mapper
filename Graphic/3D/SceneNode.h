#ifndef SCENE_NODE_H
#define SCENE_NODE_H
#include "SceneNodeType.h"
#include "Drawable.h"
#include "DrawableContainer.h"
namespace Graphic
{
    namespace Graphic3D
    {
        class SceneNode
        {
        private:
            Graphic::Graphic3D::SceneNodeType _type = Graphic::Graphic3D::SceneNodeType::NONE;
            Graphic::Graphic3D::Drawable* _drawable = nullptr;
            void* _container = nullptr; // Ze wzgledu na to ze nie wiadomo jakiego typu sa obiekty wewnatrz.
        public:
        };
    }
}
#endif