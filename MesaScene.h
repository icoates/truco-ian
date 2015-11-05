#include "Scene.h"
#include "Carta.h"


class MesaScene : public Scene
{
private:	
	std::map<unsigned int, Carta *> m_cartas;
	std::string nombres[4];

	float prop = (float)Iw2DGetSurfaceWidth() / (float) RevesWidth;
	float fixpropx = (prop / 12)* (float)RevesWidth;
	float fixpropy = (prop / 12) * (float)RevesHeight;
	float xmedio = ((float)Iw2DGetSurfaceWidth() - fixpropx - 40) / 2;
	float xderecha = ((float)Iw2DGetSurfaceWidth() - fixpropy - 10);
	float ymedio = ((float)Iw2DGetSurfaceHeight() - fixpropx - 40) / 2;
	float yabajo = ((float)Iw2DGetSurfaceHeight() - fixpropy - 10);
	float xmin = ((float)Iw2DGetSurfaceWidth() - fixpropx - 40) / 2;
	float ymin = ((float)Iw2DGetSurfaceHeight() - fixpropy - 10);
	float xmax = xmin + 40 + CartaWidth;
	float ymax = ymin + CartaHeight;
	float prop2 = (float)Iw2DGetSurfaceWidth() / (float)CartaWidth;
	float xzise = (prop2 / 10)* (float)CartaWidth;
	float ysize = (prop2 / 10)* (float)CartaHeight;
	float xCartaDerecha = ((float)Iw2DGetSurfaceWidth() - fixpropy - 20 - xzise);
	float yCartaAbajo = ((float)Iw2DGetSurfaceHeight() - fixpropy - 20 - ysize);
	float yMasoBajo = (float)Iw2DGetSurfaceHeight() - 10 - (float)sqrt((xzise*xzise) + (ysize*ysize));
	float xmasoDer = (float)Iw2DGetSurfaceWidth() - 10 - (float)sqrt((xzise*xzise) + (ysize*ysize));
	float propmaso = (float)Iw2DGetSurfaceWidth() / MasoWidth;
	float xsizeMaso = (propmaso / 6) * MasoWidth;
	float ysizeMaso = (propmaso / 6) * MasoHeight;
	
public:
	MesaScene();
	~MesaScene();
	void initMesa(int jugador, int muestra, std::string pnom[4]);
	void Render();
	void CleanUp();
	void LimpiarMesa();
	bool HitTest(float, float);
	void DoAction(SceneParamBean * spm);
	void Update();
};