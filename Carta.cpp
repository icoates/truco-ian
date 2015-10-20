#include "Carta.h"


Carta::Carta(DropTargetList* targetList)
{
	SetTargetList(targetList);
}


Carta::~Carta()
{
	if (imag != NULL){
		delete imag;
	}

}


void Carta::init(float posx, float posy, int nroCt){
	this->pos =  CIwFVec2(posx, posy);
	this->nroCarta = nroCt;
	int posCarta = 0;
	if (nroCarta < 11){
		posCarta = nroCarta;
		this->strPath = "map-bastos2.png";
	}
	else if (nroCarta < 21){
		posCarta = nroCarta % 10;
		this->strPath = "map-copas.png";
	}
	else if (nroCarta < 31){
		posCarta = nroCarta % 20;
		this->strPath = "map-espadas.png";
	}
	else {
		posCarta = nroCarta % 30;
		this->strPath = "map-oros.png";
	}
	this->offset = CIwFVec2(posCarta * 144, 0);
	this->tamaño = CIwFVec2(144, 226);
	this->imag = Iw2DCreateImage(this->strPath.c_str());
	showCarta = true;
}

void Carta::Render(){
	if (showCarta){
		if (IsDragging()){
			CIwFVec2 temp = GetDragVector();
			pos.x += temp.x;
			pos.y += temp.y;
			BeginDrag(GetLastPosition());
		}


		if (this->imag != nullptr){
			Iw2DDrawImageRegion(this->imag, this->pos, this->offset, this->tamaño);
		}
	}
}