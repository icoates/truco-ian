#include "BoxTarget.h"

BoxTarget::BoxTarget(std::string imagen, CIwFVec2 vetor)
{
	Pozo = Iw2DCreateImage(imagen.c_str());
	Position = vetor;
}


BoxTarget::~BoxTarget()
{
	if (Pozo !=NULL)
		delete Pozo;
}

void BoxTarget::Render(){
	Iw2DDrawImage(Pozo, Position);
}

