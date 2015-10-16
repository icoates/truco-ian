#include "main.h"

#include "IwDebug.h"
#include "PointerProxy.h"
#include "GameController.h"

ManoScene::ManoScene(){
	 
};

void ManoScene::init(int cuno, int cdos, int ctres){
	gDragDropManager = new DragDropManager();
	
	target = new BoxTarget("abrir.png", CIwFVec2(400, 220));
	AddTarget(target);
	AddCarta(1, cuno);
	AddCarta(2, cdos);    
	AddCarta(3, ctres); 
	
	 
}





MesaScene::MesaScene(){

}

MesaScene::~MesaScene(){
	
}

void MesaScene::init(){
	CIw2DImage * temp = Iw2DCreateImage("maso2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("maso", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("maso", CIwFVec2(400, 10)));

	temp = Iw2DCreateImage("reves2.png");
	float prop = (float)Iw2DGetSurfaceWidth() / temp->GetWidth();
	float fixpropx = temp->GetWidth()*prop / 12;  
	float fixpropy = temp->GetHeight()*prop / 12; 
	float xmedio = ((float)Iw2DGetSurfaceWidth() - fixpropx - 40) / 2;
	float xderecha = ((float)Iw2DGetSurfaceWidth() - fixpropy - 10);
	float ymedio = ((float)Iw2DGetSurfaceHeight() - fixpropx - 40) / 2;
	float yabajo = ((float)Iw2DGetSurfaceHeight() - fixpropy - 10);
	m_size.insert(std::pair<std::string, CIwFVec2>("reves", CIwFVec2(fixpropx, fixpropy)));
	m_size.insert(std::pair<std::string, CIwFVec2>("reves90", CIwFVec2(fixpropy, fixpropx)));

	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves1", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves1", CIwFVec2(xmedio, 10)));
	

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves2", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves2", CIwFVec2(xmedio+20, 10)));
	

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves3", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves3", CIwFVec2(xmedio+40, 10)));
	
	
	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves4", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves4", CIwFVec2(10, ymedio)));
	

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves5", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves5", CIwFVec2(10, ymedio+20)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves6", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves6", CIwFVec2(10, ymedio+40)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves7", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves7", CIwFVec2(xmedio, yabajo)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves8", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves8", CIwFVec2(xmedio+20, yabajo)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves9", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves9", CIwFVec2(xmedio+40, yabajo)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves10", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves10", CIwFVec2(xderecha, ymedio)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves11", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves11", CIwFVec2(xderecha, ymedio+20)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves12", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves12", CIwFVec2(xderecha, ymedio+40)));

}

void MesaScene::CleanUp(){
	DeleteObj();

	for (std::map<std::string, CIw2DImage *>::iterator it = m_imagenes.begin(); it != m_imagenes.end(); ++it){
		if (it->second != nullptr)
			delete it->second;
	}
	m_imagenes.clear();
}
void MesaScene::Render(){
	Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_NONE);
	getBackGround()->Render();
	for (std::map<std::string, CIw2DImage *>::iterator it = m_imagenes.begin(); it != m_imagenes.end(); ++it){
		//IW_2D_IMAGE_TRANSFORM_ROT90 
		

		if (it->first == "maso")
			Iw2DDrawImage(it->second, m_pos.find(it->first)->second); 
		else{
			if (it->first == "reves4" || it->first == "reves5" || it->first == "reves6" || it->first == "reves10" || it->first == "reves11" || it->first == "reves12"){
				Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_ROT90);
				Iw2DDrawImage(it->second, m_pos.find(it->first)->second, m_size.find("reves90")->second);
			}
			else {
				Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_NONE);
				Iw2DDrawImage(it->second, m_pos.find(it->first)->second, m_size.find("reves")->second);
			}
			
		}
	}
}



void ConsumePointerProxyEvents()
{
	PointerProxy *proxy = PointerProxy::singleton();
	// consume up/down events
	TouchInfoDeque::iterator itr;
	for (itr = proxy->ClickEvents.begin(); itr != proxy->ClickEvents.end(); ++itr)
	{
		if (itr->active)
			gDragDropManager->BeginDragging(MouseEventInfo(itr->id, itr->x, itr->y, ButtonDown));
		else
			gDragDropManager->EndDragging(MouseEventInfo(itr->id, itr->x, itr->y, ButtonUp));
	}
	proxy->ClickEvents.clear();

	// also feed motion only when position changes
	for (itr = proxy->MoveEvents.begin(); itr != proxy->MoveEvents.end(); ++itr)
	{
		if (itr->active)
			gDragDropManager->UpdateDragging(MouseEventInfo(itr->id, itr->x, itr->y, ActiveMotion));
	}
	proxy->MoveEvents.clear();
}

void Initialize()
{
	//Initialise graphics system(s)
	IwGxInit();
	Iw2DInit();
	// register for touch callbacks with marmalade system
	PointerProxy::singleton()->RegisterCallbacks();
}

void Terminate()
{
	delete gDragDropManager;
	
	PointerProxy::singleton()->Unregister();
	PointerProxy::singleton()->DestroySingleton();

	Iw2DTerminate();
	IwGxTerminate();
}

int main()
{
	Initialize();
	IwGxSetColClear(0x2f, 0x3f, 0x3f, 0xff);


	Background *bg = new Background();
	bg->Init("fieltro2.jpg", (float)Iw2DGetSurfaceWidth(), (float)Iw2DGetSurfaceHeight());
	ManoScene *ms = new ManoScene();
	
	ms->SetBackGround(bg);
	ms->init(2, 4, 5);
	
	Background *bg2 = new Background();
	bg2->Init("mesa.png", (float)Iw2DGetSurfaceWidth(), (float)Iw2DGetSurfaceHeight());
	MesaScene *mesa = new MesaScene();
	mesa->SetBackGround(bg2);
	mesa->init();
	GameController *game = new GameController();
	game->AddScene("mano",ms);
	game->AddScene("mesa", mesa);
	game->SetScene("mesa");
	
	while (!s3eDeviceCheckQuitRequest()){

		//Update the input systems
		s3eKeyboardUpdate();
		s3ePointerUpdate();
		 
		ConsumePointerProxyEvents();

		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
		game->Render();
		//ms->RenderMano();
		Iw2DSurfaceShow();
		// Standard EGL-style flush of drawing to the surface
		IwGxFlush();
		IwGxSwapBuffers();
		s3eDeviceYield();
	}
	game->CleanUp();
	delete ms;
	delete mesa;
	delete game;
	Terminate();

	return 0;
}