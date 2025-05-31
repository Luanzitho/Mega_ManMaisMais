#pragma once
#include "Personagem.h"

class Megaman:public Personagem
{
private:
	bool player1;
	int pontos;
	bool noChao;
	float velocidade;
	float velVertical;
	float aceleracao;
	float gravidade;
	float velMax;

public:
	Megaman();
	Megaman(bool player);
	~Megaman();
	void mover(float dt);
	//void atirar();
	void executar(float dt);
	std::string getTextureFile();
};

