#include "Scene.h"


Scene::Scene()
{
	m_bg = NULL;
	param = nullptr;
}

void Scene::SetBackGround(Background *bg)
{
	m_bg = bg;
}


void Scene::DeleteObj(){
	if (m_bg != NULL)
		delete m_bg;
	
}
void Scene::CleanUp()
{
	DeleteObj();
}

void Scene::Update()
{
	

	
}

void Scene::Move()
{
	

	
}

void Scene::RenderBG(){
	m_bg->Render();
}

void Scene::Render()
{	
	RenderBG();	
}

void Scene::DoAction(SceneParamBean * scm){

}
bool Scene::HitTest(float x, float y)
{
	return false;
}

void Scene::SetParamBean(int jugador, int carta){
	param = new SceneParamBean();
	param->SetPlayer(jugador);
	param->SetCarta(carta);
}

void Scene::ResetAction(){
	action = false;
	if (param!=nullptr)
		delete param;
}