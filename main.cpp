#include "main.h"

#include "IwDebug.h"
#include "PointerProxy.h"
#include "GameController.h"

 

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
	  
	 
	Resources::singleton()->DestroySingleton(); 

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
	bg->Init("mano", (float)Iw2DGetSurfaceWidth(), (float)Iw2DGetSurfaceHeight());
	ManoScene *ms = new ManoScene();
	
	ms->SetBackGround(bg);
	//ms->init(2, 4, 5);
	
	Background *bg2 = new Background();
	bg2->Init("mesa", (float)Iw2DGetSurfaceWidth(), (float)Iw2DGetSurfaceHeight());
	MesaScene *mesa = new MesaScene();
	mesa->SetBackGround(bg2);
	//mesa->init();
	GameController *game = new GameController();
	game->AddScene("mano",ms);
	game->AddScene("mesa", mesa); 
	game->SetScene("mesa");
	game->InitMano();
	while (!s3eDeviceCheckQuitRequest()){ 
		 
		//Update the input systems 
		s3eKeyboardUpdate(); 
		s3ePointerUpdate(); 
		 		  
		game->Update(); 

		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
		game->Render();
		
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