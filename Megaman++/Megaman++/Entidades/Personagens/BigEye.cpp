#include "BigEye.h"

BigEye::BigEye() : direita(false), noChao(false), gravidade(300), velocidade(0), velVertical(0), velMax(50), aceleracao(100), timerAtaque(0)
{
	setNumVidas(20);
}

BigEye::~BigEye()
{
}

void BigEye::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	sf::Vector2f alvo = pMega->getCoords();

	timerAtaque += dt; //Quando o timer atinge 3.5 ele pode pular

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);
	else
		velocidade = velocidade * 0.9;

	if (!noChao)
	{
		velVertical += gravidade * dt;

		if (direita) //Só se movimenta se estiver no ar
			velocidade += velMax;
		else
			velocidade -= velMax;
	}
	else
	{
		if (alvo.x > getCoords().x) //Só confere as coordenadas do player quando o BigEye está no chão
			direita = true;
		else
			direita = false;

		if (timerAtaque >= 3.5)
		{
			velVertical = 0;			
			velVertical = -350.f;
			noChao = false;

			timerAtaque = 0;
		}
	}

	posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	if (posicao.y + getTamanho().y >= 600)
	{
		posicao.y = 600 - getTamanho().y;
		noChao = true;
	}

	setCoords(posicao);
}

void BigEye::executar(float dt)
{
	mover(dt);
}

void BigEye::danificar(Megaman* p)
{
	p->operator--();
}

std::string BigEye::getTextureFile()
{
	return "Sprites/Inimigos/BigEye1-blue.png";
}