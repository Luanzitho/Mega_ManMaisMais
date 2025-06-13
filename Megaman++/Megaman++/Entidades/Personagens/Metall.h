#pragma once

#include "Inimigo.h"
#include "Megaman.h"
#include "../Projeteis/ProjetilMetall.h"

class Gerenciador_Colisoes;

class Metall:public Inimigo //Equivalente a Inimigo_facil
{
private:
	float timerEsconder;
	float timerAtirar;
	bool escondido;
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;
	ProjetilMetall* tiro;

public:
	Metall();
	~Metall();
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* GC);
	void atirar(int tipo);
	void esconder();
	void revelar();
	void executar(float dt);
	void mover(float dt);
	void danificar(Megaman* p);
	void machucar(int dmg);
	std::string getTextureFile();
};

