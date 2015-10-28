#pragma once

#include "IwGx.h" //ojo esto venia de game
#include <string> //ojo que esto estaba en player
#include "Resources.h"

class Background
{

	float width, height;
	CIw2DImage *bg;
	

public:
	Background();
	~Background();
	void Render();
	void Init(std::string path, float w, float h);
};

