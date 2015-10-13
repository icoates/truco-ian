#include "Scene.h"

class ManoScene : public Scene
{
	BoxTarget * target;
	
public:
	ManoScene();
	void init(int uno, int cdos, int ctres);
	
	void RenderMano();
	void CleanMano();
};

class MesaScene : public Scene
{
public:
		MesaScene();
		void init();
};