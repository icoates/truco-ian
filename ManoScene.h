#include "Scene.h"
#include "Carta.h"
#include "BoxTarget.h"

class ManoScene : public Scene
{
	BoxTarget * target;
	std::map<int, Carta *> imagenes;
	void CheckCartas();
	DropTargetList* targetList;
	
public:
	ManoScene();
	void init(int uno, int cdos, int ctres);
	void Update();
	void Render();
	void CleanUp();
	void AddTarget(BoxTarget *);
	void AddCarta(int indice, int nroCarta);
	
};