#include "ManoScene.h"

ManoScene::ManoScene(){
	Background *bg = new Background();
	bg->Init("mano", (float)Iw2DGetSurfaceWidth(), (float)Iw2DGetSurfaceHeight());
	SetBackGround(bg);
};



void ManoScene::Update(){
	PointerProxy *proxy = PointerProxy::singleton();
	// consume up/down events
	if (!gDragDropManager->Draggables.empty()){
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
		CheckCartas();
	}
}

void ManoScene::Render(){
	RenderBG();
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it)
	{
		it->second->Render();
	}

	target->Render();
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

void ManoScene::LimpiarMano(){
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it)
	{

		delete it->second;
	}


	if (target){
		delete target;
		target = 0;
	}

	if (targetList){
		delete targetList;
		targetList = 0;
	}


	imagenes.clear();
}

void ManoScene::CleanUp(){
	DeleteObj();
	LimpiarMano();
}



void ManoScene::AddCarta(int indice, int nroCarta){
	//permite meter repetidas pero no debería ser problema


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

	for (int i = 0; i < 3; i++){
		AddCarta(i + 1, mano[i]);
	}
	AddCarta(4, muestra);

}