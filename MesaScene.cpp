#include "MesaScene.h"



MesaScene::MesaScene(){
	Background* bg2 = new Background();
	bg2->Init("mesa", (float)Iw2DGetSurfaceWidth(), (float)Iw2DGetSurfaceHeight());
	SetBackGround(bg2);
}

MesaScene::~MesaScene(){

}

void MesaScene::initMesa(int jugador, int muestra, std::string pNom[4]){
	
	for (int i = 0; i < 4; i++){
		nombres[i] = pNom[i];
	}
	
//	Iw2DSetFont(gpResources->getFont());
	
	
	float xmaso;
	float ymaso;	

	Carta * cTemp = new Carta(NULL);

	if (jugador == 3){
		
		cTemp->init(50, 25, muestra);
		cTemp->SetRot(135);
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		m_cartas.insert(std::pair<unsigned int, Carta*>(0, cTemp));
	}
	else if (jugador == 4) {
		
		cTemp->init(50, yMasoBajo , muestra);
		cTemp->SetRot(45);
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		m_cartas.insert(std::pair<unsigned int, Carta*>(0, cTemp));
	}
	else if (jugador == 1){
		cTemp->init(xmasoDer, yMasoBajo, muestra);
		cTemp->SetRot(315);
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		m_cartas.insert(std::pair<unsigned int, Carta*>(0, cTemp));
	}
	else if (jugador == 2){
		cTemp->init(xmasoDer, 25, muestra);
		cTemp->SetRot(225);
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		m_cartas.insert(std::pair<unsigned int, Carta*>(0, cTemp));
	}

	if (jugador == 1){
		xmaso = (float)Iw2DGetSurfaceWidth() - 10 - xsizeMaso;
		ymaso = (float)Iw2DGetSurfaceHeight() - 10 - ysizeMaso;
	}
	else if (jugador == 2){
		xmaso = (float)Iw2DGetSurfaceWidth() - 10 - xsizeMaso;
		ymaso = 10;
	}
	else if (jugador == 3){
		xmaso = 10;
		ymaso = 10;
	}
	else if (jugador == 4){
		xmaso = 10;
		ymaso = (float)Iw2DGetSurfaceHeight() - 10 - ysizeMaso;
	}
	
	

	cTemp = new Carta(NULL);
	cTemp->init(xmaso, ymaso, CodMazo);
	
	cTemp->SetSize(CIwFVec2(xsizeMaso,ysizeMaso));

	m_cartas.insert(std::pair<int, Carta*>(-1, cTemp));

	

	cTemp = new Carta(NULL);
	cTemp->init(xmedio, yabajo, CodReves);
	m_cartas.insert(std::pair<int, Carta *>(1, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xmedio + 20, yabajo, CodReves);
	m_cartas.insert(std::pair<int, Carta *>(2, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xmedio + 40, yabajo, CodReves);
	m_cartas.insert(std::pair<int, Carta *>(3, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xderecha, ymedio, CodReves);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(4, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xderecha, ymedio + 20, CodReves);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(5, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xderecha, ymedio + 40, CodReves);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(6, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xmedio, 10, CodReves);
	m_cartas.insert(std::pair<int, Carta *>(7, cTemp));
	

	cTemp = new Carta(NULL);
	cTemp->init(xmedio + 20, 10, CodReves);
	m_cartas.insert(std::pair<int, Carta *>(8, cTemp));
	

	cTemp = new Carta(NULL);
	cTemp->init(xmedio + 40, 10, CodReves);
	m_cartas.insert(std::pair<int, Carta *>(9, cTemp));

	
	cTemp = new Carta(NULL);
	cTemp->init(10, ymedio, CodReves);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(10, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(10, ymedio + 20, CodReves);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(11, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(10, ymedio + 40, CodReves);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(12, cTemp));
	
}



void MesaScene::Render(){
	Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_NONE);
	getBackGround()->Render();
	for (std::map<unsigned int, Carta *>::iterator it = m_cartas.begin(); it != m_cartas.end(); ++it){		
		//IwDebugTraceLinePrintf("CARTA: %d", it->first);
		it->second->Render();
	}
	
//	Iw2DDrawString(nombres[0].c_str(), CIwFVec2(xmedio +21, yabajo + 20), CIwFVec2(50, 20), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
	//Iw2DDrawString(nombres[1].c_str(), CIwFVec2(xderecha, ymedio +20), CIwFVec2(50, 20), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
	//Iw2DDrawString(nombres[2].c_str(), CIwFVec2(xmedio + 21, 30), CIwFVec2(122, 133), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
	//Iw2DDrawString(nombres[3].c_str(), CIwFVec2(10, ymedio+20), CIwFVec2(122, 133), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
	
}

bool MesaScene::HitTest(float x, float y){

	
	

	if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
		return true;
	return false;
}

void MesaScene::Update(){
	PointerProxy *proxy = PointerProxy::singleton();
	// consume up/down events
	TouchInfoDeque::iterator itr;
	if (gpGameState->GetEstado() == ManoJugando){
		
		for (itr = proxy->ClickEvents.begin(); itr != proxy->ClickEvents.end(); ++itr)
		{
			if (HitTest((float)itr->x, (float)itr->y)){
				SetAction(true);
			}
			else
				SetAction(false);

		}
		
	}
	else if (gpGameState->GetEstado()== TerminoMano){
		std::map<unsigned int, Carta *>::iterator it = m_cartas.find(55);
		if (it != m_cartas.end()){
			//la cagamooooo
		}
		for (itr = proxy->ClickEvents.begin(); itr != proxy->ClickEvents.end(); ++itr)
		{
			if (  it->second->IsInside(CIwFVec2((float)itr->x, (float)itr->y))){
				SetAction(true);
				delete it->second;
				m_cartas.erase(55);
				LimpiarMesa();
				
			}
			else
				SetAction(false);

		}
	}
	proxy->ClickEvents.clear();


	proxy->MoveEvents.clear();
}

void MesaScene::LimpiarMesa(){
	for (std::map<unsigned int, Carta *>::iterator it = m_cartas.begin(); it != m_cartas.end(); ++it){
		IwDebugTraceLinePrintf("MUESTRA: %d", it->first);
		if (it->second != NULL)
			delete it->second;
	}
	m_cartas.clear();
}

void MesaScene::CleanUp(){
	DeleteObj();
	LimpiarMesa();
}
void MesaScene::DoAction(SceneParamBean *scm){
	
	
	Carta * cTemp = new Carta(NULL);

	
	if (scm->GetPlayer() == 1){
		cTemp->init(xmedio + 20, yCartaAbajo, scm->GetCarta());
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		std::map<unsigned int, Carta *>::iterator it = m_cartas.find(20);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(20);
		}
		m_cartas.insert(std::pair<unsigned int, Carta *>(20, cTemp));
		it = m_cartas.find(3);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(3);
		}
		else{
			it = m_cartas.find(2);
			if (it != m_cartas.end()){
				delete it->second;
				m_cartas.erase(2);
			}
			else{
				it = m_cartas.find(1);
				if (it != m_cartas.end()){
					delete it->second;
					m_cartas.erase(1);
				}
			}
		}
	}
	else if (scm->GetPlayer() == 2){
		cTemp->init(xCartaDerecha, ymedio, scm->GetCarta());
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		std::map<unsigned int, Carta *>::iterator it = m_cartas.find(21);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(21);
		}
		m_cartas.insert(std::pair<unsigned int, Carta *>(21, cTemp));
		it = m_cartas.find(6);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(6);
		}
		else{
			it = m_cartas.find(5);
			if (it != m_cartas.end()){
				delete it->second;
				m_cartas.erase(5);
			}
			else{
				it = m_cartas.find(4);
				if (it != m_cartas.end()){
					delete it->second;
					m_cartas.erase(4);
				}
			}
		}
	}
	else if (scm->GetPlayer() == 3){
		float yarriba = 20 + fixpropy;
		cTemp->init(xmedio+20, yarriba , scm->GetCarta());
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		std::map<unsigned int, Carta *>::iterator it = m_cartas.find(22);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(22);
		}
		m_cartas.insert(std::pair<unsigned int, Carta *>(22, cTemp));
		it = m_cartas.find(9);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(9);
		}
		else{
			it = m_cartas.find(8);
			if (it != m_cartas.end()){
				delete it->second;
				m_cartas.erase(8);
			}
			else{
				it = m_cartas.find(7);
				if (it != m_cartas.end()){
					delete it->second;
					m_cartas.erase(7);
				}
			}
		}
	}
	else if (scm->GetPlayer() == 4){
		
		cTemp->init(20 + fixpropy, ymedio, scm->GetCarta());
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		std::map<unsigned int, Carta *>::iterator it = m_cartas.find(23);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(23);
		}
		m_cartas.insert(std::pair<unsigned int, Carta *>(23, cTemp));
		it = m_cartas.find(12);
		if (it != m_cartas.end()){
			delete it->second;
			m_cartas.erase(12);
		}
		else{
			it = m_cartas.find(11);
			if (it != m_cartas.end()){
				delete it->second;
				m_cartas.erase(11);
			}
			else{
				it = m_cartas.find(10);
				if (it != m_cartas.end()){
					delete it->second;
					m_cartas.erase(10);
				}
			}
		}
	}

	if (scm->GetRefresh() > 0){
		//IwDebugTraceLinePrintf("VA A DAR: %d", scm->GetRefresh());
		float xr = 0;
		float yr = 0;
		Carta * cTemp2 ;
		cTemp2 = new Carta(NULL);
		cTemp2->init(10, 10, Codrefresh);

		//no pregunto por el 3 porque ahi seria 10 10 q es con lo que inicializa arriba
		if (scm->GetRefresh() == 1){
			cTemp2->SetPos(CIwFVec2((float)Iw2DGetSurfaceWidth() - cTemp2->GetSize().x - 10, (float)Iw2DGetSurfaceHeight() - cTemp2->GetSize().y - 10));
		}
		else if (scm->GetRefresh() == 2){
			cTemp2->SetPos(CIwFVec2((float)Iw2DGetSurfaceWidth() - cTemp2->GetSize().x - 10,  10));
		}
		else if (scm->GetRefresh() == 4){
			cTemp2->SetPos(CIwFVec2(10, (float)Iw2DGetSurfaceHeight() - cTemp2->GetSize().y - 10));
		}
		m_cartas.insert(std::pair<int, Carta*>(55, cTemp2));
		
		gpGameState->SetEstado(TerminoMano);
	}
}