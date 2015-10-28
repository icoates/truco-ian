#include "MesaScene.h"



MesaScene::MesaScene(){

}

MesaScene::~MesaScene(){

}

void MesaScene::init(int jugador, int muestra){
	
	Carta * cTemp;

	
	float prop = (float)Iw2DGetSurfaceWidth() / (float) RevesWidth;
	float fixpropx = (prop / 12)* (float)RevesWidth;
	float fixpropy = (prop / 12) * (float)RevesHeight;
	float xmedio = ((float)Iw2DGetSurfaceWidth() - fixpropx - 40) / 2;
	float xderecha = ((float)Iw2DGetSurfaceWidth() - fixpropy - 10);
	float ymedio = ((float)Iw2DGetSurfaceHeight() - fixpropx - 40) / 2;
	float yabajo = ((float)Iw2DGetSurfaceHeight() - fixpropy - 10);


	cTemp = new Carta(nullptr);
	cTemp->init(xmedio, yabajo, 0);
	m_cartas.insert(std::pair<int, Carta *>(1, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(xmedio +20, yabajo, 0);
	m_cartas.insert(std::pair<int, Carta *>(2, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(xmedio + 40, yabajo, 0);
	m_cartas.insert(std::pair<int, Carta *>(3, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(xderecha, ymedio, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(4, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(xderecha, ymedio +20, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(5, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(xderecha, ymedio + 40, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(6, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(xmedio, 10, 0);
	m_cartas.insert(std::pair<int, Carta *>(7, cTemp));
	

	cTemp = new Carta(nullptr);
	cTemp->init(xmedio +20, 10, 0);
	m_cartas.insert(std::pair<int, Carta *>(8, cTemp));
	

	cTemp = new Carta(nullptr);
	cTemp->init(xmedio +40, 10, 0);
	m_cartas.insert(std::pair<int, Carta *>(9, cTemp));

	
	cTemp = new Carta(nullptr);
	cTemp->init(10, ymedio, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(10, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(10, ymedio + 20, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(11, cTemp));

	cTemp = new Carta(nullptr);
	cTemp->init(10, ymedio + 40, 0);
	cTemp->SetTransformation(IW_2D_IMAGE_TRANSFORM_ROT90);
	m_cartas.insert(std::pair<int, Carta *>(12, cTemp));
	
}

void MesaScene::CleanUp(){
	DeleteObj();

	for (std::map<unsigned int, Carta *>::iterator it = m_cartas.begin(); it != m_cartas.end(); ++it){
		IwDebugTraceLinePrintf("MUESTRA: %d", it->first);
		if (it->second != nullptr)
			delete it->second;
	}
	m_cartas.clear();
}

void MesaScene::Render(){
	Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_NONE);
	getBackGround()->Render();
	for (std::map<unsigned int, Carta *>::iterator it = m_cartas.begin(); it != m_cartas.end(); ++it){
		//IW_2D_IMAGE_TRANSFORM_ROT90 
		it->second->Render();
	}
}

bool MesaScene::HitTest(float x, float y){

	float prop = (float)Iw2DGetSurfaceWidth() / (float) RevesWidth;
	float fixpropx = (prop / 12)* (float) RevesWidth;
	float fixpropy = (prop / 12) * (float) RevesHeight;
	float xmin = ((float)Iw2DGetSurfaceWidth() - fixpropx - 40) / 2;
	float ymin = ((float)Iw2DGetSurfaceHeight() - fixpropy - 10);	
	float xmax = xmin + 40 + CartaWidth;	
	float ymax = ymin + CartaHeight;

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
		if (HitTest((float)itr->x, (float)itr->y))
			SetAction(true);
		else
			SetAction(false);

	}
	proxy->ClickEvents.clear();


	proxy->MoveEvents.clear();
}

void MesaScene::DoAction(SceneParamBean *scm){
	float prop = (float)Iw2DGetSurfaceWidth() / (float)RevesWidth;
	float fixpropx = (prop / 12)* (float)RevesWidth;
	float fixpropy = (prop / 12) * (float)RevesHeight;
	
	float prop2 = (float)Iw2DGetSurfaceWidth() / (float)CartaWidth;
	float xzise = (prop2 / 10)* (float) CartaWidth;
	float ysize = (prop2 / 10)* (float) CartaHeight;

	float xderecha = ((float)Iw2DGetSurfaceWidth() - fixpropy - 20 - xzise);
	float ymedio = ((float)Iw2DGetSurfaceHeight() - fixpropx - 40) / 2;
	float xmedio = ((float)Iw2DGetSurfaceWidth() - fixpropx - 40) / 2;
	float yabajo = ((float)Iw2DGetSurfaceHeight() - fixpropy - 20 - ysize) ;
	
	Carta * cTemp = new Carta(nullptr);
	if (scm->GetPlayer() == 1){
		cTemp->init(xmedio + 20, yabajo, scm->GetCarta());
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
		cTemp->init(xderecha, ymedio, scm->GetCarta());
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

}