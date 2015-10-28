#include "Resources.h"
#include "Resources.h"

Resources* gpResources = 0;

void Resources::init(){
	bastos = Iw2DCreateImage("map-bastos.jpg");
	copas = Iw2DCreateImage("map-copas.jpg");
	oros = Iw2DCreateImage("map-oros.jpg");
	espadas = Iw2DCreateImage("map-espadas.jpg");
	maso =  Iw2DCreateImage("maso2.png");
	reves = Iw2DCreateImage("reves2.png");
	mesa = Iw2DCreateImage("mesa.png");
	fieltro = Iw2DCreateImage("fieltro2.jpg");
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
	delete gpResources;
	gpResources = 0;
}