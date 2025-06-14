#pragma once

#include "Inimigo.h"
#include "../Projeteis/ProjetilCutMan.h"

class CutMan:public Inimigo
{
private:
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;
	ProjetilCutMan* tiro;
	short int forca;
	bool podeAtirar;
	float velMax;
	float timerAtirar;
	float timerPerseguir;
	float timerPular;
	float cooldownNoChao;

public:
	CutMan();
	~CutMan();
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* GC);
	void atirar();
	void possoAtirar();
	void mover(float dt);
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
};

