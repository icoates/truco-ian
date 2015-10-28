#include "GameController.h"
#include <ctime>


GameController::GameController()
{
	//Esto en realidad se deberá hacer con las comunicación a efectos de hacer pruebas se pone aquí
	currentPlayer = new Player("Ian", 4, false);
	jugadores.insert(std::pair<int, Player *>(1, currentPlayer));
	Player * temp = new Player("Ricca", 3, false);
	jugadores.insert(std::pair<int, Player *>(2, temp));
	temp = new Player("Peter", 2, false);
	jugadores.insert(std::pair<int, Player *>(3, temp));
	temp = new Player("Taru", 1, true);
	jugadores.insert(std::pair<int, Player *>(4, temp));
}


GameController::~GameController()
{
}


void GameController::AddScene(std::string id, Scene *scene)
{
	m_scenes.insert(std::pair<std::string, Scene*>(id, scene));
	currentScene = id;
}

void GameController::SetScene(std::string id)
{
	currentScene = id;
}

std::string GameController::GetCurrentScene()
{
	return currentScene;
}

Scene* GameController::GetScene(std::string id)
{
	std::map<std::string, Scene*>::iterator it = m_scenes.find(id);
	if (it == m_scenes.end())
		return NULL;
	else
		return it->second;
}

void GameController::CleanUp()
{
	for (std::map<std::string, Scene*>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
	{
		it->second->CleanUp();
	}

	m_scenes.clear();
	for (std::map<int, Player *>::iterator it = jugadores.begin(); it != jugadores.end(); it++){
		delete it->second;
	}
	jugadores.clear();

	
}

void GameController::Render()
{
	m_scenes[currentScene]->Render();
}



void GameController::Update(){
	m_scenes[currentScene]->Update();
	if (m_scenes[currentScene]->GetAction() && currentScene == "mesa"){
		m_scenes[currentScene]->ResetAction();
		currentScene = "mano";
		return;
	}
	else if (m_scenes[currentScene]->GetAction() && currentScene == "mano"){
		m_scenes["mesa"]->DoAction(m_scenes[currentScene]->GetParamBean());
		
//		TirarCarta(m_scenes[currentScene]->GetParamBean());
		m_scenes[currentScene]->ResetAction();
		currentScene = "mesa";
		return;
	}
}

void GameController::InitMaso(){
	std::map<int, int> tempMaso;
	int iTemp;
	int j = 0;
	for (int i = 0; i < 40; i++){
		maso[i] = 0;
		tempMaso.insert(std::pair<int, int>(i, i+1));
	}
	srand(time(NULL));

	for (int i = 0; i < 40; i++){
		iTemp = rand() % (40 - i) + 1;
		j = 1;
		for (std::map<int, int>::iterator it = tempMaso.begin(); it != tempMaso.end(); it++){
			if (j == iTemp){
				maso[i] = it->second;
				tempMaso.erase(it->first);
				break;
			}
			j++;
		}		
	}	
} 
 
int GameController::nroJugadorReparte(){

	if (currentPlayer->GetReparte()) 
		return 1; 
	else{
		int iDiff = 5 - currentPlayer->GetNroJugador();
			
		for (std::map<int, Player *>::iterator it = jugadores.begin(); it != jugadores.end(); it++){
			if (it->second->GetReparte()){
				if (iDiff == 4)
					return it->second->GetNroJugador();
				else
				   iDiff+= it->second->GetNroJugador();

				if (iDiff > 4)
					return iDiff % 4;
				else
					return iDiff;
			}

		}
	}
	return 0;
}

void GameController::Repartir(){
	int iTemp= nroJugadorReparte();	
	((MesaScene *)m_scenes["mesa"])->init(iTemp, maso[40-13]);
	((ManoScene *)m_scenes["mano"])->init();
	int j = 1;
	for (int i = 0; i < 12; i++){
		if ((iTemp + i + 1) % 4 == 1){
			
			((ManoScene *)m_scenes["mano"])->AddCarta(j, maso[40 - i-1]);
			j++;
		}
	}
}
void GameController::InitMano(){
	if (currentPlayer->GetReparte()){
		InitMaso();
		Repartir();
		currentPlayer->SetReparte(false);
		//Reparte el siguiente hay que actualizar el estado
		
	}
	else{
		//No se deberia repartir el maso, solo deberian venir por comunicacion
		InitMaso();
		Repartir();
	}
}