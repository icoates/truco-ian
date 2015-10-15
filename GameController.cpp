#include "GameController.h"
#include "scene.h"

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
