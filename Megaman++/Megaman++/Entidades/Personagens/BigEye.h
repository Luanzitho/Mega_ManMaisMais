#pragma once

#include "Inimigo.h"

class BigEye:public Inimigo //Equivalente a inimigo médio
{
private:
	float gravidade;
	float aceleracao;
	float velMax;
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

