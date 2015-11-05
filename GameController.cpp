#include "GameController.h"
#include <ctime>


GameController::GameController()
{
	//Esto en realidad se deberá hacer con las comunicación a efectos de hacer pruebas se pone aquí
	currentPlayer = new Player("Ian", 3, false);
	jugadores.insert(std::pair<int, Player *>(1, currentPlayer));
	Player * temp = new Player("Ricca", 1, false);
	jugadores.insert(std::pair<int, Player *>(2, temp));
	temp = new Player("Peter", 4, false);
	jugadores.insert(std::pair<int, Player *>(3, temp));
	temp = new Player("Taru", 2, true);
	jugadores.insert(std::pair<int, Player *>(4, temp));

	if (!gpGameState)
		gpGameState = GameState::Singleton();
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
		delete it->second;
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

int GameController::GetNroJugadorRelativo(int nroJugador){
	int iDiff = 5 - currentPlayer->GetNroJugador();
	if (nroJugador + iDiff == 4)
		return 4;
	return (nroJugador + iDiff)%4;
	return 0;
}

void GameController::TirarCarta(int jugador, int carta){
	SceneParamBean * scm = new SceneParamBean();
	scm->SetPlayer(GetNroJugadorRelativo(jugador));
	scm->SetCarta(carta);
	if (jugador == 4 && tirada == 3){
		
			scm->SetRefresh(nroJugadorReparte());
	}
	m_scenes["mesa"]->DoAction(scm);
	delete scm;
}
void GameController::Update(){
	m_scenes[currentScene]->Update();

	if (gpGameState->GetEstado() == ManoJugando){

		if (m_scenes[currentScene]->GetAction() && currentScene == "mesa"){
			m_scenes[currentScene]->ResetAction();
			//SceneParamBean * scm = new SceneParamBean();

			currentScene = "mano";
			return;
		}
		else if (m_scenes[currentScene]->GetAction() && currentScene == "mano"){
			m_scenes["mesa"]->DoAction(m_scenes[currentScene]->GetParamBean());
			tirada++;
			if (tirada == 1){
				TirarCarta(1, maso[38]);
				TirarCarta(2, maso[37]);
				TirarCarta(4, maso[36]);
			}
			else if (tirada == 2){
				TirarCarta(1, maso[34]);
				TirarCarta(2, maso[33]);
				TirarCarta(4, maso[32]);
			}
			else{
				TirarCarta(1, maso[30]);
				TirarCarta(2, maso[29]);
				TirarCarta(4, maso[28]);
			}
			//		TirarCarta(m_scenes[currentScene]->GetParamBean());
			m_scenes[currentScene]->ResetAction();
			currentScene = "mesa";
			return;
		}
	}
	else if (gpGameState->GetEstado()==TerminoMano){
		//aca habría que ver quien da si es el current o si hay que esperar a que llegue el mensaje del que da
		if (m_scenes[currentScene]->GetAction() && currentScene == "mesa"){
			m_scenes[currentScene]->ResetAction();
			((ManoScene *) m_scenes["mano"])->LimpiarMano();
			((MesaScene *)m_scenes["mesa"])->LimpiarMesa();
			InitMano();
			gpGameState->SetEstado(ManoJugando);
		}
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
	muestra = maso[40 - 13];
	j = 0;
	for (int i = 0; i < 12; i++){
		if (( i + 1) % 4 == 1){
			mano[j] = maso[40 - i - 1];			
			j++;
		}
	}
	//mano[1] = 14;
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

std::string GameController::GetNombreIndex(int nroRel){
	for (std::map<int, Player *>::iterator it = jugadores.begin(); it != jugadores.end(); it++){
		if (it->second->GetNroJugador() == nroRel)
			return (it->second->GetNombre());
	}
	return ("");
}

void GameController::Repartir(){
	int iTemp= nroJugadorReparte();	
	std::string nombres[4];
	nombres[0] = currentPlayer->GetNombre();
	int jTemp;
	for (int i = 1; i < 4; i++){
		jTemp = currentPlayer->GetNroJugador() + i;
		if (jTemp > 4) jTemp = jTemp % 4;
		nombres[i] = GetNombreIndex(jTemp);
	}
	
	
	((MesaScene *)m_scenes["mesa"])->initMesa(iTemp, muestra ,nombres);

	((ManoScene *)m_scenes["mano"])->init(mano,muestra);
	
}




void GameController::SetReparteSiguiente(){
	int reparte = 0;
	for (std::map<int, Player *>::iterator it = jugadores.begin(); it != jugadores.end(); it++){
		if (it->second->GetReparte()){
			reparte = it->second->GetNroJugador();
			it->second->SetReparte(false);
		}
	}
	reparte++;
	if (reparte == 5) reparte = 1;
	for (std::map<int, Player *>::iterator it = jugadores.begin(); it != jugadores.end(); it++){
		if (it->second->GetNroJugador() == reparte)
			it->second->SetReparte(true);
	}
}
void GameController::InitMano(){
	if (!gpGameState)
		gpGameState = GameState::Singleton();

	tirada = 0;
	gpGameState->SetEstado(ManoJugando);

	if (currentPlayer->GetReparte()){
		InitMaso();
		Repartir();
		
		//Reparte el siguiente hay que actualizar el estado
		
	}
	else{
		//No se deberia repartir el maso, solo deberian venir por comunicacion
		InitMaso();
		Repartir();
	}
	SetReparteSiguiente();

}

void GameController::Init(){
	ManoScene *ms = new ManoScene();
	MesaScene *mesa = new MesaScene();
	AddScene("mano", ms);
	AddScene("mesa", mesa);
	SetScene("mesa");
	InitMano();
}