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
	int muestra;
	int mano[3];
	int tirada = 0;
	void InitMaso();
	void Repartir();
	int GetNroJugadorRelativo(int nroJugador);	
	void TirarCarta(int jugador, int carta);
	void SetReparteSiguiente();
	int nroJugadorReparte();
	std::string GetNombreIndex(int nro);
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
	void Init();
};

