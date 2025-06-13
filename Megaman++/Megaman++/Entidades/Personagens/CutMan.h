#pragma once
#include "Inimigo.h"
class CutMan:public Inimigo
{
private:
	short int forca;
	float timerAtirar;

public:
	CutMan();
	~CutMan();
	void atirar();
	void mover(float dt);
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
};

