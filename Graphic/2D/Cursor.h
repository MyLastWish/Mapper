#ifndef CURSOR_H
#define CURSOR_H
#include <functional>
namespace Graphic
{
	namespace Graphic2D
	{
		class Cursor
		{
		private:
			float _lastX = 0.0f;
			float _lastY = 0.0f;
			float _changeX = 0.0f;
			float _changeY = 0.0f;
			bool _initializingRun = true;
			std::function<void(float, float)> _cursorMovementReaction;
		public:
			Cursor();
			void Update(float, float);
			void UpdateAndReact(float, float);
			void SetCursorMovementReaction(const std::function<void(float, float)>&);
		};
	}
}
#endif // !CURSOR_H
