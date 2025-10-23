#pragma once

#include "Inimigo.h"

class BigEye:public Inimigo //Equivalente a inimigo médio
{
private:
	float aceleracao;
	float timerAtaque;
	int danoNormal;
	float raio;
	static int indiceBig;

public:
	BigEye();
	~BigEye();
	void saltar();
	void saltar(int chance);
	void mover(float dt);
	int getFrame();
	sf::Vector2f getEscalaCorreta();
	void executar(float dt);
	void danificar(Megaman* p);
	std::string getTextureFile();
	void salvar();
	void carregar();
	static void resetIndice() { indiceBig = -1; }
};

