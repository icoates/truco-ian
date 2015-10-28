#include "Scene.h"
#include "Carta.h"


class MesaScene : public Scene
{
private:	
	std::map<unsigned int, Carta *> m_cartas;
	
public:
	MesaScene();
	~MesaScene();
	void init(int jugador, int muestra);
	void Render();
	void CleanUp();
	bool HitTest(float, float);
	void DoAction(SceneParamBean * spm);
	void Update();
};