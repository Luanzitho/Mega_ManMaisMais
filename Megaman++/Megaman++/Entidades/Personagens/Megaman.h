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
	int pontos;
	//float aceleracao;
	float velMax;
	float cooldownTiro;
	float tempoCooldown;
	ProjetilMegaman* tiro;
	//std::vector<ProjetilMegaman*> disparos;
	ListaEntidades* LE;
	Gerenciador_Colisoes* GC;
	float cooldownNoChao;

public:
	Megaman();
	Megaman(bool player);
	~Megaman();
	void associaListaEntidades(ListaEntidades* pLista);
	void associaGerenciadorColisoes(Gerenciador_Colisoes* GC);
	void mover(float dt);
	void atirar(float dt);
	void executar(float dt);
	std::string getTextureFile();
};

