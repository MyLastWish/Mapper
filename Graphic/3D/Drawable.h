#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Shader.h"
#include "Positionable.h"
#include "../API/Data/Mat4.h"
namespace Graphic
{
    namespace Graphic3D
    {
        class Drawable : public Graphic::Graphic3D::Positionable
        {
        protected:
            virtual void _drawObject(Graphic::Shader*);
        public:
            Drawable();
            void Draw(Graphic::Shader*);
        };
    }
}
#endif