#pragma once
class SceneParamBean
{
	int player;
	int carta;
public:
	SceneParamBean();
	~SceneParamBean();
	int GetPlayer(){ return player; }
	int GetCarta(){ return carta; }
	void SetPlayer(int tplayer){player = tplayer;}
	void SetCarta(int tcarta){ carta = tcarta; }


};

