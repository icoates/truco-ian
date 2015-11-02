#include "MesaScene.h"



MesaScene::MesaScene(){

}

MesaScene::~MesaScene(){

}

void MesaScene::init(int jugador, int muestra, std::string pNom[4]){
	
	for (int i = 0; i < 4; i++){
		nombres[i] = pNom[i];
	}
	if (gpResources == 0)
		gpResources = Resources::singleton();
//	Iw2DSetFont(gpResources->getFont());
	
	Carta * cTemp;
	float prop2 = (float)Iw2DGetSurfaceWidth() / (float)CartaWidth;
	float xzise = (prop2 / 10)* (float)CartaWidth;
	float ysize = (prop2 / 10)* (float)CartaHeight;
	float xmaso;
	float ymaso;
	float yBajo = (float)Iw2DGetSurfaceHeight() - 10 - (float) sqrt((xzise*xzise) + (ysize*ysize));
	float xmasoDer = (float)Iw2DGetSurfaceWidth() - 10 - (float) sqrt((xzise*xzise) + (ysize*ysize));
	float propmaso = (float)Iw2DGetSurfaceWidth() / MasoWidth;
	float xsizeMaso = (propmaso / 6) * MasoWidth;
	float ysizeMaso = (propmaso / 6) * MasoHeight;

	cTemp = new Carta(NULL);

	if (jugador == 3){
		
		cTemp->init(50, 25, muestra);
		cTemp->SetRot(135);
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		m_cartas.insert(std::pair<unsigned int, Carta*>(0, cTemp));
	}
	else if (jugador == 4) {
		
		cTemp->init(50, yBajo , muestra);
		cTemp->SetRot(45);
		cTemp->SetSize(CIwFVec2(xzise, ysize));
		m_cartas.insert(std::pair<unsigned int, Carta*>(0, cTemp));
	}
	else if (jugador == 1){
		cTemp->init(xmasoDer, yBajo, muestra);
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
	cTemp->init(xmaso, ymaso, 41);
	
	cTemp->SetSize(CIwFVec2(xsizeMaso,ysizeMaso));

	m_cartas.insert(std::pair<int, Carta*>(-1, cTemp));

	

	cTemp = new Carta(NULL);
	cTemp->init(xmedio, yabajo, 0);
	m_cartas.insert(std::pair<int, Carta *>(1, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xmedio +20, yabajo, 0);
	m_cartas.insert(std::pair<int, Carta *>(2, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xmedio + 40, yabajo, 0);
	m_cartas.insert(std::pair<int, Carta *>(3, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xderecha, ymedio, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(4, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xderecha, ymedio +20, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(5, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xderecha, ymedio + 40, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(6, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(xmedio, 10, 0);
	m_cartas.insert(std::pair<int, Carta *>(7, cTemp));
	

	cTemp = new Carta(NULL);
	cTemp->init(xmedio +20, 10, 0);
	m_cartas.insert(std::pair<int, Carta *>(8, cTemp));
	

	cTemp = new Carta(NULL);
	cTemp->init(xmedio +40, 10, 0);
	m_cartas.insert(std::pair<int, Carta *>(9, cTemp));

	
	cTemp = new Carta(NULL);
	cTemp->init(10, ymedio, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(10, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(10, ymedio + 20, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(11, cTemp));

	cTemp = new Carta(NULL);
	cTemp->init(10, ymedio + 40, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(12, cTemp));
	
}

void MesaScene::CleanUp(){
	DeleteObj();

	for (std::map<unsigned int, Carta *>::iterator it = m_cartas.begin(); it != m_cartas.end(); ++it){
//		IwDebugTraceLinePrintf("MUESTRA: %d", it->first);
		if (it->second != NULL)
			delete it->second;
	}
	m_cartas.clear();
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
	for (itr = proxy->ClickEvents.begin(); itr != proxy->ClickEvents.end(); ++itr)
	{
		if (HitTest((float)itr->x, (float)itr->y)){
		SetAction(true);
		
		}
		else
			SetAction(false);

	}
	proxy->ClickEvents.clear();


	proxy->MoveEvents.clear();
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

}