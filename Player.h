#pragma once
#include <string>
class Player
{
private:
	std::string strNombre;
	int intJugador;
	bool bReparte;
	bool jugandoMano=true;
public:
	Player(std::string nombreParam, int NroParam, bool reparteParam);
	~Player();
	std::string GetNombre(){ return strNombre; }
	int GetNroJugador() { return intJugador; }
	bool GetReparte() { return bReparte; }
	void SetReparte(bool reparteParam) { bReparte = reparteParam; }
	bool GetJugandoMano() { return jugandoMano; }
	void SetJugandoMano(bool pjugando){ jugandoMano = pjugando; }

};

