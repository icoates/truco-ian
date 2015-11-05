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
	gDragDropManager = new DragDropManager();
}  
 
void Terminate()  
{
	
	delete gDragDropManager; 
	gDragDropManager = 0;
	GameState::Singleton()->DeleteSingleton();
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
	GameController *game = new GameController();
	
	game->Init();

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
	
	delete game;
	
	Terminate();

	return 0;
}