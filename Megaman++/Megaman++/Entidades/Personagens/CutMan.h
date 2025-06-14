#pragma once
#include "Inimigo.h"
class CutMan:public Inimigo
{
private:
	short int forca;
	float velMax;
	float timerAtirar;
	float timerPerseguir;
	float timerPular;
	float cooldownNoChao;

public:
	CutMan();
	~CutMan();
	void atirar();
	void mover(float dt);
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
};

