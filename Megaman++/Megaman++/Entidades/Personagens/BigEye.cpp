#include "BigEye.h"

BigEye::BigEye() : gravidade(300), velocidade(0), velVertical(0), velMax(50), aceleracao(100), timerAtaque(0)
{
	setNumVidas(20);
}

BigEye::~BigEye()
{
}

void BigEye::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocidade -= velMax;
		direita = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocidade += velMax;
		direita = true;
	}
	//else
	//	velocidade = velocidade * 0.9;
	*/

	timerAtaque += dt;

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);

	if (!noChao) //Confere se ele está no chão, se sim, consegue pular, se não, sofre efeito da gravidade
		velVertical += gravidade * dt;
	else
	{
		if (timerAtaque >= 3.5) //Temos ainda que fazer ele saber onde o jogador está para seguir ele, temos que fazer ele se mover para a direção só enquanto
			//pula e impedir que ele mude a direção no ar
		{
			velVertical = 0;
			{
				velVertical = -300.f;
				noChao = false;
			}
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