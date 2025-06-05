#pragma once

#include "Personagem.h"
#include "../Projeteis/ProjetilMegaman.h"
#include "../../Listas/ListaEntidades.h"
#include <vector>

class Megaman:public Personagem
{
public://private:
	bool player1;
	bool direita;
	bool noChao;
	int pontos;
	float velocidade;
	float velVertical;
	float aceleracao;
	float gravidade;
	float velMax;
	ProjetilMegaman tiro;
	ListaEntidades* LE;

public:
	Megaman();
	Megaman(bool player);
	~Megaman();
	void associaListaEntidades(ListaEntidades* lista);
	void mover(float dt);
	void atirar(float dt);
	void executar(float dt);
	std::string getTextureFile();
};

