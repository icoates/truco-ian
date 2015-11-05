#include "Carta.h"


Carta::Carta(DropTargetList* targetList)
{
	SetTargetList(targetList);
}

 
Carta::~Carta()
{
	//if (imag != NULL){
	//	delete imag;
	//}

}


void Carta::init(float posx, float posy, int nroCt){ 
	
	this->pos = CIwFVec2(posx, posy);
	this->nroCarta = nroCt;
	if (CodReves == nroCarta){
		imag = gpResources->getReves();
		//strPath = "reves2.png";
		offset = CIwFVec2(0, 0);
		float rwidth = RevesWidth;
		float rHeight = RevesHeight;
		float prop = (float)Iw2DGetSurfaceWidth() / rwidth;
		float fixpropx = prop*rwidth / 12;
		float fixpropy = rHeight*prop / 12;
		tamanio = CIwFVec2(rwidth, rHeight);
		size = CIwFVec2(fixpropx, fixpropy);
	}
	else if (nroCarta == CodMazo){
		imag = gpResources->getMaso();
		//strPath = "maso2.png";  
		offset = CIwFVec2(0, 0);
		float mwidth = MasoWidth;
		float mHeight = MasoHeight;
		float prop = (float)Iw2DGetSurfaceWidth() / mwidth;
		float fixpropx = prop*mwidth / prop;
		float fixpropy = mHeight*prop / prop;
		tamanio = CIwFVec2(mwidth, mHeight);
		size = CIwFVec2(fixpropx, fixpropy);
	}
	else if (nroCarta == CodRefresh){
		imag = gpResources->getRefresh();
		offset = CIwFVec2(0, 0);
		float prop = (float)Iw2DGetSurfaceWidth() / RefreshWidth;
		float fixpropx = (prop / 12) * RefreshWidth;
		tamanio = CIwFVec2(RefreshWidth, RefreshWidth);
		size = CIwFVec2(fixpropx, fixpropx);
	}
	else{
		int posCarta = 0;
		if (nroCarta < 11){
			posCarta = nroCarta - 1;
			imag = gpResources->getBastos();
			//this->strPath = "map-bastos2.png";
		}
		else if (nroCarta < 21){
			posCarta = nroCarta % 10 - 1;
			imag = gpResources->getCopas();
			//this->strPath = "map-copas.png";
		}
		else if (nroCarta < 31){
			posCarta = nroCarta % 20 - 1;
			imag = gpResources->getEspadas();
			//this->strPath = "map-espadas.png";
		}
		else {
			posCarta = nroCarta % 30 - 1;
			imag = gpResources->getOros();
			//this->strPath = "map-oros.png";
		}
		float cWidth = CartaWidth;
		float cHeight = CartaHeight;
		this->offset = CIwFVec2((float)posCarta * cWidth, 0);
		this->tamanio = CIwFVec2(cWidth, cHeight);
		this->size = CIwFVec2(cWidth, cHeight);
	}
	//this->imag = Iw2DCreateImage(this->strPath.c_str());
	showCarta = true;
}

void Carta::Render(){
	if (showCarta){
		if (IsDragging()){
			CIwFVec2 temp = GetDragVector();
			pos.x += temp.x;
			pos.y += temp.y;
			BeginDrag(GetLastPosition());
		}
		
		if (nroRot == 0){
			Iw2DSetImageTransform(transform);
			if (this->imag != NULL){
				Iw2DDrawImageRegion(this->imag, this->pos, this->size, this->offset, this->tamanio);
			}
		}
		else
		{ 
			CIwFMat2D lMatrix;
			//IwDebugTraceLinePrintf("MUESTRA: %d", nroCarta);
			lMatrix.SetRot(nroRot * PI / 180, CIwFVec2(pos.x+(size.x/2),  pos.y+(size.y/2)));
			Iw2DSetTransformMatrix(lMatrix);
			
			if (this->imag != NULL){
				Iw2DDrawImageRegion(this->imag, this->pos, CIwFVec2(size.x,size.y), this->offset, this->tamanio);
			}

		}


		
		Iw2DSetTransformMatrix(CIwFMat2D::g_Identity);
	}
}

void Carta::SetTransformation(CIw2DImageTransform pTransform){
	transform = pTransform;
	
	if (transform == IW_2D_IMAGE_TRANSFORM_ROT90 || transform== IW_2D_IMAGE_TRANSFORM_ROT270){
		size = CIwFVec2(size.y, size.x);
	}
}