#pragma once

#include "Personagem.h"
#include "../Projeteis/ProjetilMegaman.h"
#include "../../Listas/ListaEntidades.h"
#include <vector>

class Megaman:public Personagem
{
private:
	bool player1;
	bool direita;
	int pontos;
	float gravidade;
	float aceleracao;
	float velMax;
	float cooldownTiro;
	float tempoCooldown;
	ProjetilMegaman tiro;
	//std::vector<ProjetilMegaman*> disparos;
	ListaEntidades* LE;
	float cooldownNoChao;

public:
	Megaman();
	Megaman(bool player);
	~Megaman();
	void associaListaEntidades(ListaEntidades* pLista);
	void mover(float dt);
	void atirar(float dt);
	void executar(float dt);
	std::string getTextureFile();
};

