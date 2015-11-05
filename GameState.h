#pragma once

enum eGameState
{
	ManoJugando = 0,    //  Se est� jugando una mano
	TerminoMano = 1,    //  Todos jugaron y se est� esperando que se reparta de nuevo

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