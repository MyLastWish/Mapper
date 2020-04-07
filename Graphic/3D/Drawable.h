#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Shader.h"
namespace Graphic
{
    namespace Graphic3D
    {
        class Drawable
        {
        public:
            virtual void Draw(Graphic::Shader*) {}
        };
    }
}
#endif