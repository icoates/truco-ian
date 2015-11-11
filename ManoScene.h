#include "Scene.h"
#include "Carta.h"
#include "BoxTarget.h"

class ManoScene : public Scene
{
	BoxTarget * target;
	BoxTarget * volver;
	BoxTarget * irse;
	
	std::map<int, Carta *> imagenes;

	//std::map<int, DropTargetList*> listaTargets;
	void CheckCartas();
	DropTargetList* targetList;
	
public:
	ManoScene();
	void init(int mano[3], int muestra);
	void Update();
	void Render();
	void CleanUp();
	void LimpiarMano();
	void AddTarget(BoxTarget *);
	void AddCarta(int indice, int nroCarta);

};