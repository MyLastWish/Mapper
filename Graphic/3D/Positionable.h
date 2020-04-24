#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include "../../API/Data/Vec3.h"
#include "../../API/Data/Mat4.h"
#include "../Shader.h"
namespace Graphic
{
    namespace Graphic3D
    {
        class Positionable
        {
        protected:
			API::Data::Vec3 _position;
			API::Data::Vec3 _rotation;

            bool _transformationChanged = true;
        public:
            // Domyslny konstruktor ustawiajacy pozycje w (0, 0, 0) oraz zerowy obrot.
            Positionable();
            // Konstruktor przyjmujacy pozycje i rotacje obiektu.
            Positionable(API::Data::Vec3, API::Data::Vec3);
			void SetRotation(API::Data::Vec3);
			void SetPosition(API::Data::Vec3);
            virtual API::Data::Mat4 GetTransformationMatrix() const;
            void UpdateTransformation(Graphic::Shader*);
        };
    }
}
#endif
