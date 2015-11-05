#pragma once
class SceneParamBean
{
	int player;
	int carta;
	int refresh = 0;
public:
	SceneParamBean();
	~SceneParamBean();
	int GetPlayer(){ return player; }
	int GetCarta(){ return carta; }
	int GetRefresh(){ return refresh; }
	void SetPlayer(int tplayer){player = tplayer;}
	void SetCarta(int tcarta){ carta = tcarta; }
	void SetRefresh(int prefresh) { refresh = prefresh; }


};

