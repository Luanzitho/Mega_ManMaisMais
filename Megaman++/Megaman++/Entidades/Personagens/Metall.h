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
	int tamanho;
	static int indiceMetall;

public:
	Metall();
	~Metall();
	//void associaListaEntidades(ListaEntidades* pLista);
	//void associaGerenciadorColisoes(Gerenciador_Colisoes* GC);
	void atirar(const int tipo);
	void esconder();
	void revelar();
	void executar(float dt);
	void mover(float dt);
	void danificar(Megaman* p);
	void machucar(const int dmg);
	std::string getTextureFile();
	void salvar();
	void carregar();
};

