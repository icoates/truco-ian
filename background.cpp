#include "background.h"

Background::Background()
{
	bg = NULL;
	width = 0;
	height = 0;
}

Background::~Background()
{
	//if (bg != NULL)
	//	delete bg;
}

void Background::Init(std::string path, float w, float h)
{
	if (!gpResources)
		gpResources = Resources::singleton();

	if (path == "mesa")
		bg = gpResources->getMesa();
	else if (path == "mano"){
		bg = gpResources->getFieltro();
		flag = true;
	}
	width = w;
	height = h;
	
}

void Background::Render()
{	
	float imgWidth = bg->GetWidth();
	float imgHeight = bg->GetHeight();
	float iMax = width / imgWidth;
	float jMax = height / imgHeight;
	
	if (flag)
	for (float i = 0; i < (iMax*imgWidth); i += imgWidth){
		for (float j = 0; j < (jMax*imgHeight); j += imgHeight){
			Iw2DDrawImage(bg, CIwFVec2(i, j));
		}
	}
	else
		Iw2DDrawImage(bg, CIwFVec2(0,0),CIwFVec2(width,height));	
}