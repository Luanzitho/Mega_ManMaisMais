#pragma once

#include "Personagem.h"
#include "Megaman.h"
#include <time.h>

class Inimigo:public Personagem
{
protected:
	int nivel_maldade;
	int dano;
	Megaman* pMega;
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;

public:
	Inimigo();
	~Inimigo();
	//void salvarDataBuffer();
	void conhecerJogador(Megaman* p);
	virtual void mover(float dt) = 0;
	virtual void executar(float dt) = 0;
	virtual void danificar(Megaman* p) = 0;
	virtual std::string getTextureFile() = 0;
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* gc);
};