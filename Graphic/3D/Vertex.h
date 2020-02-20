#ifndef VERTEX_H
#define VERTEX_H
#include "Cartesian/Point3D.h"
#include "Cartesian/Vector3D.h"

namespace Graphic
{
	namespace Graphic3D
	{
		template <typename T = float>
		class Vertex
		{
		private:
			API::Cartesian::Point3D<T> _position;
			API::Cartesian::Vector3D<T> _normal;
		public:
			Vertex(API::Cartesian::Point3D<T> position, API::Cartesian::Vector3D<T> normal)
			{
				_position = position;
				_normal = normal;
			}
			void Move(API::Cartesian::Vector3D<T> vec)
			{
				_position.Move(vec);
			}
			API::Cartesian::Vector3D<T> GetNormal() const
			{
				return _normal;
			}
			API::Cartesian::Point3D<T> GetPosition() const
			{
				return _position;
			}
		};
	}
}
#endif