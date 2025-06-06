#pragma once

#include "Inimigo.h"

class BigEye:public Inimigo //Equivalente a inimigo médio
{
private:
	float gravidade;
	float velocidade;
	float velVertical;
	float aceleracao;
	float velMax;
	bool noChao;
	bool direita;
	float timerAtaque;

public:
	BigEye();
	~BigEye();
	void mover(float dt);
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
};

