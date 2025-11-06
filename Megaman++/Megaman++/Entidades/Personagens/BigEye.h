#pragma once

#define TEMPO_PULO 0.8
#define TEMPO_ANIMACAO_PULO 0.5

#define ALTURA_PULO -250
#define ALTURA_PULO_CRITICO -400
#define VELOCIDADE_MAX 50

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

