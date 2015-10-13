#ifndef __SCENE__
#define __SCENE__

#include "background.h"
#include "Carta.h"
#include "BoxTarget.h"
#include <map>	//ojo que esto estaba en player

class Scene
{
	
	Background * m_bg;
	std::map<int, Carta *> imagenes;
	DropTargetList* targetList;
public:
	Scene();
	void SetBackGround(Background *);
	void AddTarget(BoxTarget *);
	void AddCarta(int indice, int nroCarta);
	//void RemovePlayer(std::string);
	void CleanUp();
	//Player *GetPlayer(std::string);
	void Render();
	void Update();
	void Move();
	void HitTest(float, float);
	virtual void onHit(std::string){}
	virtual void Touch(int, float, float){}
	virtual void OnUpdate(){}
	virtual void OnMoved(){}
	virtual void OnRender(){}
};

#endif