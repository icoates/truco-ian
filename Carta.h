#pragma once
#include "Iw2D.h"
#include <string>
#include "DragDrop.h"

class Carta : public Draggable
{
private:
	int nroCarta;
	bool showCarta;
	std::string strPath;
	CIwFVec2 size;
	CIwFVec2 pos;
	CIwFVec2 offset;
	CIwFVec2 tama�o;
	CIw2DImage *imag;
	std::string transform = "none";

public:
	Carta(DropTargetList* targetList);
	~Carta();
	void init(float posx, float posy, int nroCarta );
	void IsInDrop(){ showCarta = false; };
	
	bool IsInside(CIwFVec2 posi)
	{
		float diffx = posi.x - pos.x;
		float diffy = posi.y - pos.y;

		if (diffx>0 && diffx < tama�o.x && diffy>0 && diffy < tama�o.y)
			return true;
		return false;
	}
	int GetNroCarta() { return nroCarta; }
	std::string GetPath();
	CIwFVec2 GetPos();
	CIwFVec2 GetOffset();
	CIwFVec2 GetSize();
	void BajarPoco();
	void Render();
	bool GetShow(){ return showCarta; }
};

