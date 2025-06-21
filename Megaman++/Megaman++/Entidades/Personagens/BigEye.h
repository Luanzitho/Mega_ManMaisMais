#pragma once

#include "Inimigo.h"

class BigEye:public Inimigo //Equivalente a inimigo médio
{
private:
	float aceleracao;
	float timerAtaque;
	int danoNormal;
	float raio;

public:
	BigEye();
	~BigEye();
	void saltar();
	void saltar(int i);
	void mover(float dt);
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
	void salvar();
};

