#include "Scene.h"


Scene::Scene()
{
	m_bg = NULL;
	targetList = new DropTargetList;
}

void Scene::SetBackGround(Background *bg)
{
	m_bg = bg;
}

void Scene::AddTarget(BoxTarget * target){
	targetList->Add(target);
}

void Scene::AddCarta(int indice, int nroCarta ){
	//permite meter repetidas pero no debería ser problema
	nroCarta--;
	
	
	Carta* oCar = new Carta(targetList);
	if (indice == 1){
		oCar->init(20, 20, nroCarta);
	}
	else if (indice == 2){
		oCar->init(20, 34, nroCarta);
	}
	else {
		oCar->init(20, 48, nroCarta);
	}
	imagenes.insert(std::pair<int, Carta *>(indice, oCar));
	
	gDragDropManager->Draggables.push_back(imagenes[indice]);
	

	
}

void Scene::CleanUp()
{
	if (m_bg != NULL)
		delete m_bg;

	
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it)
	{
		
		delete it->second;
	}
	delete targetList;


	imagenes.clear();

}

void Scene::Update()
{
	

	OnUpdate();
}

void Scene::Move()
{
	

	OnMoved();
}

void Scene::Render()
{
	m_bg->Render();
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it)
	{		
		it->second->Render();
	}

	OnRender();
}

void Scene::HitTest(float x, float y)
{
	
}