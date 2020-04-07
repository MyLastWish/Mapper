#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include "Data/Vec3.h"
#include "Data/Mat4.h"
namespace API
{
    namespace Graphic
    {
        class Positionable
        {
        protected:
			API::Data::Vec3 _position;
			API::Data::Vec3 _rotation;
        public:
            // Domyslny konstruktor ustawiajacy pozycje w (0, 0, 0) oraz zerowy obrot.
            Positionable();
            // Konstruktor przyjmujacy pozycje i rotacje obiektu.
            Positionable(API::Data::Vec3, API::Data::Vec3);
			void SetRotation(API::Data::Vec3);
			void SetPosition(API::Data::Vec3);
            virtual API::Data::Mat4 GetTransformationMatrix() const;
        };
    }
}
#endif
