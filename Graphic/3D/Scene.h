#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Camera.h"
#include "DrawableContainer.h"
#include "Drawable.h"
#include "SceneNode.h"
namespace Graphic
{
    namespace Graphic3D
    {
        class Scene
        {
        private:
            Graphic::Graphic3D::Camera* _camera = nullptr;
            std::vector<Graphic::Graphic3D::SceneNode*> _nodes;
        public:
            Scene(Graphic::Graphic3D::Camera*);
            
        };
    }
}
#endif 