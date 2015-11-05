#pragma once

#include "DragDrop.h"
#include "Iw2D.h"
#include <string>

class BoxTarget : public DropTarget
{
private:
	CIw2DImage * Pozo;
	CIwFVec2	Position;
	CIwFVec2	Size;

public:
	BoxTarget(std::string, CIwFVec2);
	~BoxTarget();
	void Render();
	void SetSize(CIwFVec2 pSize){ Size = pSize; }
	virtual bool IsInside(CIwFVec2 pos, Draggable* source)
	{
		float diffx = pos.x - Position.x;
		float diffy = pos.y - Position.y;

		if (diffx>0 && diffx < Size.x && diffy>0 && diffy< Size.y)
		{
			return true;
		}
		return false;
	}


};