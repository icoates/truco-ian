#include "Player.h"


Player::Player(std::string nombreParam, int nroParam, bool reparteParam)
{
	strNombre = nombreParam;
	intJugador = nroParam;
	bReparte = reparteParam;
}


Player::~Player()
{
}
