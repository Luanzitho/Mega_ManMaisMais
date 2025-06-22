#pragma once

#include "Inimigo.h"
#include "../Projeteis/ProjetilCutMan.h"

class CutMan:public Inimigo
{
private:
	short int forca;
	bool podeAtirar;
	float timerAtirar;
	float timerPerseguir;
	float timerPular;
	float cooldownNoChao;
	static int indiceCutMan;

public:
	CutMan();
	~CutMan();
	void atirar();
	void possoAtirar();
	void mover(float dt);
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
	void salvar();
	void carregar();
	bool getPossoAtirar();
};

