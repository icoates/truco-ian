#include "GameController.h"



GameController::GameController()
{
}


GameController::~GameController()
{
}


void GameController::AddScene(std::string id, Scene *scene)
{
	m_scenes.insert(std::pair<std::string, Scene*>(id, scene));
	currentScene = id;
}

void GameController::SetScene(std::string id)
{
	currentScene = id;
}

std::string GameController::GetCurrentScene()
{
	return currentScene;
}

Scene* GameController::GetScene(std::string id)
{
	std::map<std::string, Scene*>::iterator it = m_scenes.find(id);
	if (it == m_scenes.end())
		return NULL;
	else
		return it->second;
}

void GameController::CleanUp()
{
	for (std::map<std::string, Scene*>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
	{
		IwDebugTraceLinePrintf("Cleaning %s", it->first.c_str());
		it->second->CleanUp();
	}

	m_scenes.clear();
}

void GameController::Render()
{
	m_scenes[currentScene]->Render();
}

void GameController::TirarCarta(SceneParamBean * param){
	int jugador = param->GetPlayer();
	int carta = param->GetCarta();

	//Segun el jugador tengo que posicionar la carta en un distinto lugar y borrar una de la cantidad que tenga en la mesaScene

}


void GameController::Update(){
	m_scenes[currentScene]->Update();
	if (m_scenes[currentScene]->GetAction() && currentScene == "mesa"){
		m_scenes[currentScene]->SetAction(false);
		currentScene = "mano";
		return;
	}
	else if (m_scenes[currentScene]->GetAction() && currentScene == "mano"){
//		TirarCarta(m_scenes[currentScene]->GetParamBean());
		m_scenes[currentScene]->ResetAction();
		currentScene = "mesa";
		return;
	}
}

