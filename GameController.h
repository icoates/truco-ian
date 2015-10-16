#pragma once

#include "s3e.h"
#include "IwGx.h"
#include "Iw2D.h"
#include <string>
#include <map>
#include "scene.h"

class GameController
{
private:
	std::map<std::string, Scene*> m_scenes;
	std::string currentScene;
	
	
public:
	GameController();
	~GameController();
	void AddScene(std::string, Scene *);
	void SetScene(std::string);
	std::string GetCurrentScene();
	void CleanUp();
	void Render();	
	void Update();
	Scene* GetScene(std::string);
	void TirarCarta(SceneParamBean * param);
};

