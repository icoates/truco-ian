#ifndef __SCENE__
#define __SCENE__

#include "background.h"

#include <map>	//ojo que esto estaba en player
#include "PointerProxy.h"
#include "SceneParamBean.h"

class Scene
{
	
	Background * m_bg;	
	bool action = false;
	SceneParamBean * param;

public:
	
	Scene();
	void SetBackGround(Background *);
	void DeleteObj();
	Background * getBackGround(){ return m_bg; };
	
	
	virtual void CleanUp();
	void RenderBG();
	virtual void Render();
	virtual bool HitTest(float x, float y);
	virtual void Update();
	virtual void DoAction(SceneParamBean *);
	void Move();
	bool GetAction(){ return action; }
	void SetAction(bool eaction){ action = eaction; }
	void SetParamBean(int, int);
	SceneParamBean * GetParamBean(){ return param; }
	void ResetAction();
};

#endif