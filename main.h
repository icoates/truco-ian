#include "Scene.h"

class ManoScene : public Scene
{
	BoxTarget * target;
	
public:
	ManoScene();
	void init(int uno, int cdos, int ctres);
	
};

class MesaScene : public Scene
{
private:
	std::map<std::string, CIw2DImage*> m_imagenes;
	std::map<std::string, CIwFVec2> m_pos;
public:
		MesaScene();
		~MesaScene();
		void init();
		void Render();
		void CleanUp();

};