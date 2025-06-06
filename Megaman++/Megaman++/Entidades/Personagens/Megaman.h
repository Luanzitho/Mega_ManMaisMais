#pragma once

#include "Personagem.h"
#include "../Projeteis/ProjetilMegaman.h"
#include "../../Listas/ListaEntidades.h"
#include <vector>

class Megaman:public Personagem
{
private://private:
	bool player1;
	bool direita;
	bool noChao;
	int pontos;
	float gravidade;
	float velocidade;
	float velVertical;
	float aceleracao;
	float velMax;
	float cooldownTiro;
	float tempoCooldown;
	ProjetilMegaman tiro;
	//std::vector<ProjetilMegaman*> disparos;
	ListaEntidades* LE;

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

