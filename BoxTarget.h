#pragma once

#include "DragDrop.h"
#include "Iw2D.h"
#include <string>

class BoxTarget : public DropTarget
{
private:
	CIw2DImage * Pozo;
	CIwFVec2	Position;

public:
	BoxTarget(std::string , CIwFVec2 );
	~BoxTarget();
	void Render();
	
	virtual bool IsInside(CIwFVec2 pos, Draggable* source)
	{
		float diffx = pos.x - Position.x;
		float diffy = pos.y - Position.y;

		if (diffx>0 && diffx < Pozo->GetWidth() && diffy>0 && diffy< Pozo->GetHeight())		
		{
			return true;
		}
		return false;
	}

	
};

