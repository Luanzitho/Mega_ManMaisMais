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
	float timerBotao;
	float cooldownTiro;
	float framesInvencibilidade;
	//ProjetilMegaman* tiro;
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;
	float cooldownNoChao;
	int vidas;

public:
	Megaman();
	Megaman(bool player);
	~Megaman();
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* GC);
	void addPontos(int pts);
	void machucar(int dmg);
	void mover(float dt);
	void atirar(float dt);
	void executar(float dt);
	std::string getTextureFile();
	void setLibera(bool lib);
	bool getLibera();
};

