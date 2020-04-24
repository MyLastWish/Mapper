#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Camera.h"
#include "DrawableContainer.h"
#include "Drawable.h"
namespace Graphic
{
    namespace Graphic3D
    {
        class Scene
        {
        private:
            Graphic::Graphic3D::Camera* _camera = nullptr;
            std::vector<Graphic::Graphic3D::Drawable*> _drawables;
            unsigned _drawableCount = 0;
            Graphic::Shader* _shader = nullptr;
        public:
            Scene(Graphic::Graphic3D::Camera*, Graphic::Shader*);
            void Add(std::vector<Graphic::Graphic3D::Drawable*>);
            void Add(Graphic::Graphic3D::Drawable*); 
            void Redraw();
            void SetShader(Graphic::Shader*);
            Graphic::Shader* GetShaderPtr() const;
        };
    }
}
#endif 