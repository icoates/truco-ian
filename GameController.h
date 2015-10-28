#pragma once

#include "s3e.h"
#include "MesaScene.h"
#include "ManoScene.h"
#include "Player.h"


class GameController
{
private:
	std::map<std::string, Scene*> m_scenes;
	std::string currentScene;
	Player * currentPlayer;
	std::map<int, Player *> jugadores;
	int maso[40];

	void InitMaso();
	void Repartir();
	int nroJugadorReparte();
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
	void InitMano();
	
};

