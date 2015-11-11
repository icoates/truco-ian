#include "Resources.h"


Resources* gpResources = 0;

void Resources::init(){
	bastos = Iw2DCreateImage("map-bastos3.png");
	copas = Iw2DCreateImage("map-copas2.png");
	oros = Iw2DCreateImage("map-oros2.png");
	espadas = Iw2DCreateImage("map-espadas2.png");
	maso = Iw2DCreateImage("maso3.png");
	reves = Iw2DCreateImage("reves2.png");
	mesa = Iw2DCreateImage("mesa.png");
	fieltro = Iw2DCreateImage("fieltro2.jpg");
	refresh = Iw2DCreateImage("refresh.png");
	pozo = Iw2DCreateImage("abrir2.png");
	volver = Iw2DCreateImage("volvermesa.png");
	salida = Iw2DCreateImage("salida.png");
	
	//Font = Iw2DCreateFont("fonts/font.gxfont");
}

Resources* Resources::singleton(){
	if (!gpResources){
		gpResources = new Resources();
		gpResources->init();
	}
	return gpResources;
}

void Resources::DestroySingleton(){
	delete bastos;
	delete copas;
	delete oros;
	delete espadas;
	delete maso;
	delete mesa;
	delete fieltro;
	delete reves;
	delete refresh;
	delete pozo;
	delete volver;
	delete salida;

	//	delete Font;
	delete gpResources;
	gpResources = 0;
}