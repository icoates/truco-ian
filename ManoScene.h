#include "Scene.h"
#include "Carta.h"
#include "BoxTarget.h"

class ManoScene : public Scene
{
	BoxTarget * target;
	std::map<int, Carta *> imagenes;
	//std::map<int, DropTargetList*> listaTargets;
	void CheckCartas();
	DropTargetList* targetList;
	
public:
	ManoScene();
	void init();
	void Update();
	void Render();
	void CleanUp();
	void AddTarget(BoxTarget *);
	void AddCarta(int indice, int nroCarta);
	
};