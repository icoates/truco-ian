#pragma once

enum eGameState
{
	ManoJugando = 0,    //  Se está jugando una mano
	TerminoMano = 1,    //  Todos jugaron y se está esperando que se reparta de nuevo

};

class GameState
{
private:
	eGameState estado = ManoJugando;
public:
	eGameState GetEstado() { return estado; }
	void SetEstado(eGameState pest) { estado = pest; }
	static GameState * Singleton();
	void DeleteSingleton();
};

extern GameState * gpGameState;