#include "Cursor.h"

Graphic::Graphic2D::Cursor::Cursor()
{
}

void Graphic::Graphic2D::Cursor::Update(float x, float y)
{
	if (_initializingRun)
	{
		_lastX = x;
		_lastY = y;
		_initializingRun = false;
	}
	_changeX = x - _lastX;
	_changeY = y - _lastY;
}

void Graphic::Graphic2D::Cursor::UpdateAndReact(float x, float y)
{
	Update(x, y);
	_cursorMovementReaction(_changeX, _changeY);
}

void Graphic::Graphic2D::Cursor::SetCursorMovementReaction(const std::function<void(float, float)>& fun)
{
	_cursorMovementReaction = fun;
}