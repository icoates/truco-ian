#include "GameState.h"

 
GameState * gpGameState = 0;

GameState * GameState::Singleton(){
	if (!gpGameState){
		gpGameState = new GameState();
	}
	return gpGameState;
}

void GameState::DeleteSingleton(){
	delete gpGameState;
	gpGameState = 0;
}