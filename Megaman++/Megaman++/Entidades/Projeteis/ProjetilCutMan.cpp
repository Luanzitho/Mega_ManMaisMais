#include "ProjetilCutMan.h"

#include "../Personagens/Megaman.h"
#include "../Personagens/CutMan.h"

#include "../../Gerenciadores/Gerenciador_Colisoes.h"

#include <cmath>

#include <iostream>
ProjetilCutMan::ProjetilCutMan(): timerRetornar(0), mestre(nullptr), limite(false)
{
	setId(6);
}

ProjetilCutMan::ProjetilCutMan(sf::Vector2f posicao, int maldade, sf::Vector2f alvo, CutMan* mestre): Projetil(350, maldade + 4), timerRetornar(0), limite(false)
{
	setCoords(posicao);

	doMega = false;

	setId(6);

	this->alvo = alvo;
	this->mestre = mestre;

	direcao = alvo - getCoords(); //Referência normalização de vetor para disparas em 360º - Youtuber Suraj Sharma
	float comprimento = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
	direcao /= comprimento;

	setTamanho(sf::Vector2f(40.f, 40.f));
}

ProjetilCutMan::~ProjetilCutMan()
{
	mestre = nullptr;
}

void ProjetilCutMan::atingirMegaman(Megaman* p)
{
	if (!p || p->getNumVidas() <= 0) return;

	p->machucar(dano);
	//std::cout << "Atingido!\n";
}

void ProjetilCutMan::perseguir(float dt)
{
	sf::Vector2f posicao = getCoords();

	//posicao.y += gravidade * dt;
	velVertical -= empuxo * dt;

	posicao += direcao * velocidade * dt;
	setCoords(posicao);
}

void ProjetilCutMan::retornar(float dt)
{
	sf::Vector2f posicao = getCoords();

	direcao = mestre->getCoords() - getCoords(); //Referência normalização de vetor para disparas em 360º - Youtuber Suraj Sharma
	float comprimento = sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
	direcao /= comprimento;

	posicao += direcao * velocidade * dt;

	//posicao.y += gravidade * dt;
	velVertical -= empuxo * dt;

	setCoords(posicao);

	if (abs(posicao.x - mestre->getCoords().x) < 20 && abs(posicao.y - mestre->getCoords().y) < 15) //A lâmina retorna para a cabeça dele
	{
		mestre->possoAtirar();
		destruir();
	}
}

void ProjetilCutMan::executar(float dt)
{
	timerRetornar += dt;
	sofrerAcaoDaGravidade(dt);

	if (!(mestre->getVivo()))
		destruir();

	if (timerRetornar < 1 && !limite)
	{
		perseguir(dt);
	}

	if (timerRetornar >= 1 || limite)
	{
		retornar(dt);
	}
}

std::string ProjetilCutMan::getTextureFile()
{
	return "Sprites/Projeteis/ProjetilCutMan1.png";
}