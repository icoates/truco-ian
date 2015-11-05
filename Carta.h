#pragma once

#include "DragDrop.h"


#define RevesWidth	57.0;
#define RevesHeight	84.0;
#define MasoWidth	76;
#define MasoHeight	51;
#define CartaWidth	144;
#define CartaHeight 226;
#define PozoWidth	56;
const int RefreshWidth = 256;

const int CodMazo = 41;
const int CodReves = 0;
const int CodRefresh = 42;

class Carta : public Draggable
{
private:
	int nroCarta;
	int nroRot = 0;
	bool showCarta;
	//std::string strPath;
	CIwFVec2 size;
	CIwFVec2 pos;
	CIwFVec2 offset;
	CIwFVec2 tamanio;
	CIw2DImage *imag;
	CIw2DImageTransform transform = IW_2D_IMAGE_TRANSFORM_NONE;

public:
	Carta(DropTargetList* targetList);
	~Carta();
	void init(float posx, float posy, int nroCarta);
	void IsInDrop(){ showCarta = false; };

	bool IsInside(CIwFVec2 posi)
	{
		float diffx = posi.x - pos.x;
		float diffy = posi.y - pos.y;

		if (diffx > 0 && diffx < size.x && diffy>0 && diffy < size.y)
			return true;
		return false;
	}
	//Gets y Sets Sencillos
	int GetNroCarta() { return nroCarta; }
	//std::string GetPath() { return strPath; }
	CIwFVec2 GetPos(){ return pos; }
	CIwFVec2 GetOffset() { return offset; }
	CIwFVec2 GetSize() { return size; }
	CIwFVec2 GetTamanio() { return tamanio; }
	bool GetShow(){ return showCarta; }

	void SetPos(CIwFVec2 pPos){ pos = pPos; }
	void SetSize(CIwFVec2 pSize) { size = pSize; }
	void SetOffset(CIwFVec2 pOffset){ offset = pOffset; }
	void SetTamanio(CIwFVec2 pTam) { tamanio = pTam; }
	void SetRot(int pRot){
		nroRot = pRot;
	}
	//Funciones
	void Render();
	void SetTransformation(CIw2DImageTransform 	pTransform);
};
