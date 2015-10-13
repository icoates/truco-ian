#include "main.h"
#include "s3e.h"
#include "IwDebug.h"
#include "IwGx.h"
#include "Iw2D.h"
#include "PointerProxy.h"


ManoScene::ManoScene(){

};

void ManoScene::init(int cuno, int cdos, int ctres){
	gDragDropManager = new DragDropManager();
	
	target = new BoxTarget("abrir.png", CIwFVec2(250, 400));
	AddTarget(target);
	AddCarta(1, cuno);
	AddCarta(2, cdos);   
	AddCarta(3, ctres);
	

}

void ManoScene::RenderMano(){
	Render();
	target->Render();
}

void ManoScene::CleanMano(){
	delete target;
	CleanUp();
	
//	delete abrir;
}

void HandleSingleTouchButtonCB(s3ePointerMotionEvent* event, ManoScene *ms){
	
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
	
	

	while (!s3eDeviceCheckQuitRequest()){

		//Update the input systems
		s3eKeyboardUpdate();
		s3ePointerUpdate();

		ConsumePointerProxyEvents();

		IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);

		ms->RenderMano();
		Iw2DSurfaceShow();
		// Standard EGL-style flush of drawing to the surface
		IwGxFlush();
		IwGxSwapBuffers();
		s3eDeviceYield();
	}
	ms->CleanMano();
	delete ms;
	Terminate();

	return 0;
}