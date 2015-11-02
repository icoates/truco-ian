#include "ManoScene.h"

ManoScene::ManoScene(){
	
};

void ManoScene::init(int mano[3], int muestra){
	gDragDropManager = new DragDropManager();
	targetList = new DropTargetList;
	target = new BoxTarget("abrir.png", CIwFVec2((float)Iw2DGetSurfaceWidth()-80, (float) Iw2DGetSurfaceHeight()-80));
	targetList->Add(target);
	for (int i = 0; i < 3; i++){
		AddCarta(i + 1, mano[i]);
	}
	AddCarta(4, muestra);
	
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
	

	float prop2 = (float)Iw2DGetSurfaceWidth() / (float)CartaWidth;
	float xzise = (prop2 / 5)* (float)CartaWidth;
	float ysize = (prop2 / 5)* (float)CartaHeight;
	Carta* oCar = new Carta(targetList);
	if (indice == 1){
		oCar->init(20, 20, nroCarta);
	}
	else if (indice == 2){
		oCar->init(20, 25, nroCarta);
	}
	else if (indice ==3) {
		oCar->init(20, 30, nroCarta);
	}
	else{
		oCar->init(50 + xzise, 20, nroCarta);
		xzise = (prop2 / 10)* (float)CartaWidth;
		ysize = (prop2 / 10)* (float)CartaHeight;
		
	}
	oCar->SetSize(CIwFVec2(xzise, ysize));
	imagenes.insert(std::pair<int, Carta *>(indice, oCar));
	
	if (indice!=4)
		gDragDropManager->Draggables.push_back(imagenes[indice]);
	


}