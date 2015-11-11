#include "BoxTarget.h"

BoxTarget::BoxTarget(std::string imagen, CIwFVec2 vetor)
{
	if (imagen == "Pozo")
		Pozo = gpResources->getPozo();
	else if (imagen == "Volver")
		Pozo = gpResources->getVolver();
	else if (imagen == "Salir")
		Pozo = gpResources->getSalida();
	

	Position = vetor;
	Size = CIwFVec2(Pozo->GetWidth(), Pozo->GetHeight());
}


BoxTarget::~BoxTarget()
{
	
}

void BoxTarget::Render(){
	Iw2DDrawImage(Pozo, Position,Size);
}

