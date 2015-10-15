#pragma once

#include "s3e.h"
#include "IwGx.h"
#include "Iw2D.h"
#include <string>
#include <map>

class Scene;
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
	Scene* GetScene(std::string);
};

