#include "ManoScene.h"

ManoScene::ManoScene(){
	
};

void ManoScene::init(){
	gDragDropManager = new DragDropManager();
	targetList = new DropTargetList;
	target = new BoxTarget("abrir.png", CIwFVec2(400, 220));
	targetList->Add(target);
	/*
	AddCarta(1, cuno);	
	AddCarta(2, cdos);	
	AddCarta(3, ctres);
	*/
}

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
		if (it->second->GetShow()==false){
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

void ManoScene::CleanUp(){
	DeleteObj();
	for (std::map<int, Carta *>::iterator it = imagenes.begin(); it != imagenes.end(); ++it)
	{

		delete it->second;
	}

	delete target;
	delete targetList;
	
	
	imagenes.clear();
}



void ManoScene::AddCarta(int indice, int nroCarta){
	//permite meter repetidas pero no debería ser problema
	


	Carta* oCar = new Carta(targetList);
	if (indice == 1){
		oCar->init(20, 20, nroCarta);
	}
	else if (indice == 2){
		oCar->init(20, 34, nroCarta);
	}
	else {
		oCar->init(20, 48, nroCarta);
	}
	imagenes.insert(std::pair<int, Carta *>(indice, oCar));
	
	gDragDropManager->Draggables.push_back(imagenes[indice]);
	


}