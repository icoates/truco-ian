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
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves1", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves1", CIwFVec2(180, 10)));
	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves2", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves2", CIwFVec2(200, 10)));
	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves3", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves3", CIwFVec2(220, 10)));
	
	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves4", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves4", CIwFVec2(10, 100)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves5", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves5", CIwFVec2(10, 120)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves6", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves6", CIwFVec2(10, 140)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves7", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves7", CIwFVec2(180, 220)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves8", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves8", CIwFVec2(200, 220)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves9", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves9", CIwFVec2(220, 220)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves10", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves10", CIwFVec2(380, 100)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves11", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves11", CIwFVec2(380, 120)));

	temp = Iw2DCreateImage("reves2.png");
	m_imagenes.insert(std::pair<std::string, CIw2DImage *>("reves12", temp));
	m_pos.insert(std::pair<std::string, CIwFVec2>("reves12", CIwFVec2(380, 140)));

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
		if (it->first == "reves4" || it->first == "reves5" || it->first == "reves6" || it->first == "reves10" || it->first == "reves11" || it->first == "reves12"){
			Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_ROT90);
		}
		else {
			Iw2DSetImageTransform(IW_2D_IMAGE_TRANSFORM_NONE);
		}
		Iw2DDrawImage(it->second, m_pos.find(it->first)->second); 
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