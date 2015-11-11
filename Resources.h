#pragma once
#include "Iw2D.h"
#include "s3eDialog.h"

class Resources
{
private:
	CIw2DImage * bastos;
	CIw2DImage * copas;
	CIw2DImage * oros;
	CIw2DImage * espadas;
	CIw2DImage * maso;
	CIw2DImage * reves;
	CIw2DImage * mesa;
	CIw2DImage * fieltro;
	CIw2DImage * refresh;
	CIw2DImage * pozo;
	CIw2DImage * volver;
	CIw2DImage * salida;
	
	//	CIw2DFont * Font;
	void init();
public:
	static Resources* singleton();
	void DestroySingleton();
	CIw2DImage * getBastos(){ return bastos; }
	CIw2DImage * getCopas(){ return copas; }
	CIw2DImage * getOros(){ return oros; }
	CIw2DImage * getEspadas(){ return espadas; }
	CIw2DImage * getMaso(){ return maso; }
	CIw2DImage * getReves(){ return reves; }
	CIw2DImage * getMesa(){ return mesa; }
	CIw2DImage * getFieltro(){ return fieltro; }
	CIw2DImage * getRefresh() { return refresh; }
	CIw2DImage * getPozo() { return pozo; }
	CIw2DImage * getVolver() { return volver; }
	CIw2DImage * getSalida() { return salida; }
	
	//CIw2DFont * getFont() { return Font; }
};

extern Resources* gpResources;