#include "background.h"

Background::Background()
{
	bg = NULL;
	width = 0;
	height = 0;
}

Background::~Background()
{
	if (bg != NULL)
		delete bg;
}

void Background::Init(std::string path, float w, float h)
{
	bg = Iw2DCreateImage(path.c_str());
	width = w;
	height = h;
	
}

void Background::Render()
{	
	float imgWidth = bg->GetWidth();
	float imgHeight = bg->GetHeight();
	float iMax = width / imgWidth;
	float jMax = height / imgHeight;
	

	for (float i = 0; i < (iMax*imgWidth); i += imgWidth){
		for (float j = 0; j < (jMax*imgHeight); j += imgHeight){
			Iw2DDrawImage(bg, CIwFVec2(i, j));
		}
	}
	//Iw2DDrawImage(bg, CIwFVec2(0,0),CIwFVec2(width,height));	
}