#pragma once

#include "Personagem.h"
#include "../Projeteis/ProjetilMegaman.h"
#include "../../Listas/ListaEntidades.h"
#include <vector>

class Gerenciador_Colisoes;

class Megaman:public Personagem
{
private:
	bool player1;
	bool invencivel;
	static int pontos;
	bool teclaApertada;
	float cooldownTiro;
	float framesInvencibilidade;
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;
	float cooldownNoChao;

public:
	Megaman();
	Megaman(bool player);
	~Megaman();
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* GC);
	void operator+=(const int pts);
	void machucar(const int dmg);
	void mover(float dt);
	void atirar(float dt);
	void executar(float dt);
	std::string getTextureFile();
	void salvar();
	void carregar();
	const int getPontos();
};

