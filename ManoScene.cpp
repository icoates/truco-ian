#include "ManoScene.h"


ManoScene::ManoScene(){
	Background *bg = new Background();
	bg->Init("mano", (float)Iw2DGetSurfaceWidth(), (float)Iw2DGetSurfaceHeight());
	SetBackGround(bg);
};





void ManoScene::Render(){
	RenderBG();
	target->Render();
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it)
	{
		it->second->Render();
	}

	
	volver->Render();
	if (irse)
		irse->Render();
	
}
void ManoScene::CheckCartas(){
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it){
		if (it->second->GetShow() == false){
			SetAction(true);
			//Aca se deberia pasar el jugador por ahora para pruebas siempre es el 1
			SetParamBean(1, it->second->GetNroCarta());
			//gDragDropManager->Draggables.erase()
			DraggableList::iterator itr;
			for (itr = gDragDropManager->Draggables.begin(); itr != gDragDropManager->Draggables.end(); itr++){
				if (((Carta *)(*itr))->GetNroCarta() == it->second->GetNroCarta()){
					gDragDropManager->Draggables.erase(itr);
					break;
				}
			}
			delete it->second;
			imagenes.erase(it->first);

			//solo se juega de a una
			break;
		}
	}
}

void ManoScene::Update(){
	PointerProxy *proxy = PointerProxy::singleton();
	// consume up/down events
	if (!gDragDropManager->Draggables.empty()){
		TouchInfoDeque::iterator itr;
		for (itr = proxy->ClickEvents.begin(); itr != proxy->ClickEvents.end(); ++itr)
		{
			

			if (itr->active){
				if (volver->IsInside(CIwFVec2(itr->x, itr->y), NULL)){
					SetAction(true);
					return;
				}
				if (irse->IsInside(CIwFVec2(itr->x, itr->y), NULL)){
					s3eDialogGetError();
						if (s3eDialogAvailable()){
							
							s3eDialogAlertInfo alertBox;
							alertBox.m_Message = "¿Desea mostrar las cartas?";
							alertBox.m_Title = "Está tirando las cartas";
							alertBox.m_Button[0] = "Si";
							alertBox.m_Button[1] = "No";
							alertBox.m_Button[2] = "Cancelar";

							alertBox.m_Id = 6996;
							s3eDialogAlertBox(&alertBox);
							
						}
					
					
					//SetAction(true);
					//Aca se deberia pasar el jugador por ahora para pruebas siempre es el 1
					//SetParamBean(1, -1);
				}
				gDragDropManager->BeginDragging(MouseEventInfo(itr->id, itr->x, itr->y, ButtonDown));
			}
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
		CheckCartas();
	}
}
void ManoScene::LimpiarMano(){
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it)
	{

		delete it->second;
	}


	if (target){
		delete target;
		target = 0;
	}

	if (volver){
		delete volver;
		volver = 0;
	}

	if (irse){
		delete irse;
		irse = 0;
	}

	

	if (targetList){
		delete targetList;
		targetList = 0;
	}


	imagenes.clear();
}

int32 DialogFinishedCallback(s3eDialogCallbackData* pDialogData, void* pUserData) {
	if (pDialogData->m_Id == 6996)
	{
		if (pDialogData->m_ButtonPressed == 1)
		{
			// OK button pressed
			//SetAction(true);
			//Aca se deberia pasar el jugador por ahora para pruebas siempre es el 1
			((ManoScene *)pUserData)->SetAction(true);
			((ManoScene *)pUserData)->SetParamBean(1, -1);
			
			//SetParamBean(1, -1);
		}
		else
		{
			// Cancel button pressed
		}
	}
	// Return value is not used by system
	return 0;
}

void ManoScene::CleanUp(){
	DeleteObj();
	LimpiarMano();
	// To stop further callbacks
	s3eDialogUnRegister(S3E_DIALOG_FINISHED, (s3eCallback)DialogFinishedCallback);
}



void ManoScene::AddCarta(int indice, int nroCarta){
	//permite meter repetidas pero no debería ser problema
	//IwDebugTraceLinePrintf("VA A DAR: %d", nroCarta);

	float prop2 = (float)Iw2DGetSurfaceWidth() / (float)CartaWidth;
	float xzise = (float)(prop2 / 3.8)* CartaWidth;
	float ysize = (float)(prop2 / 3.8)* CartaHeight;
	Carta* oCar = new Carta(targetList);
	if (indice == 1){ 
		oCar->init(20, 20, nroCarta);
	}
	else if (indice == 2){
		oCar->init(20, 25, nroCarta);
	}
	else if (indice == 3) {
		oCar->init(20, 30, nroCarta);
	}
	else{
		oCar->init(50 + xzise, 20, nroCarta);
		xzise = (prop2 / 10)* (float)CartaWidth;
		ysize = (prop2 / 10)* (float)CartaHeight;

	}
	oCar->SetSize(CIwFVec2(xzise, ysize));
	imagenes.insert(std::pair<int, Carta *>(indice, oCar));

	if (indice != 4)
		gDragDropManager->Draggables.push_back(imagenes[indice]);



}

void ManoScene::init(int mano[3], int muestra){

	targetList = new DropTargetList;
	float propPozo = (float)Iw2DGetSurfaceWidth() / PozoWidth;
	float xpozosize = (propPozo / 6) * PozoWidth;

	target = new BoxTarget("Pozo", CIwFVec2((float)Iw2DGetSurfaceWidth() - xpozosize - 10, (float)Iw2DGetSurfaceHeight() - xpozosize - 10));
	target->SetSize(CIwFVec2(xpozosize, xpozosize));
	targetList->Add(target);

	float propVolver = (float)Iw2DGetSurfaceWidth() / 200;
	float volversize = (propVolver / 6) * 200;
	volver = new BoxTarget("Volver", CIwFVec2((float)Iw2DGetSurfaceWidth() - volversize - 10,  10));
	volver->SetSize(CIwFVec2(volversize, volversize));
	
	float propSalida = (float)Iw2DGetSurfaceWidth() / 234;
	float xsalidasize = (propSalida / 6) * 234;
	float ysalidasize = (propSalida / 6) * 129;
	irse = new BoxTarget("Salir", CIwFVec2((float)Iw2DGetSurfaceWidth() - xsalidasize - 10, volversize + 20));
	irse->SetSize(CIwFVec2(xsalidasize, ysalidasize));

	
	for (int i = 0; i < 3; i++){
		
		AddCarta(i + 1, mano[i]);
	}
	AddCarta(4, muestra);
	// To set up the callback
	s3eDialogRegister(S3E_DIALOG_FINISHED, (s3eCallback)DialogFinishedCallback, this);
}