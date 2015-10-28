#pragma once
#include <string>
class Player
{
private:
	std::string strNombre;
	int intJugador;
	bool bReparte;
public:
	Player(std::string nombreParam, int NroParam, bool reparteParam);
	~Player();
	std::string GetNombre(){ return strNombre; }
	int GetNroJugador() { return intJugador; }
	bool GetReparte() { return bReparte; }
	void SetReparte(bool reparteParam) { bReparte = reparteParam; }
};

