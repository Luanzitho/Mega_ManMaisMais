#include "BigEye.h"
#include <time.h>

BigEye::BigEye() : aceleracao(150), timerAtaque(0)
{
	raio = rand() % 41 + 80;

	setTamanho(sf::Vector2f(raio, 120.f));

	velMax = 50;

	qtdPontos += 200;

	if (nivel_maldade == 1)
	{
		dano = 2;
		setNumVidas(15);
	}

	else if (nivel_maldade == 2)
	{
		dano = 4;
		setNumVidas(15);
	}

	else if (nivel_maldade == 3)
	{
		dano = 4;
		setNumVidas(20);
	}
}

BigEye::~BigEye()
{
}

void BigEye::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	sf::Vector2f alvo = pMega->getCoords();

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);
	else
		velocidade = velocidade * 0.9;

	if (!noChao) //S� se movimenta se estiver no ar
	{
		//velVertical += gravidade * dt;
		
		if (direita)
			velocidade += velMax;
		else
			velocidade -= velMax;

		posicao.x += velocidade * dt;
	}

	else //Se estiver no ch�o, procura o player e pula se o timer estiver em 3.5
	{
		timerAtaque += dt; //Quando o timer atinge 3.5 o BigEye pode pular

		velocidade = 0;

		if (alvo.x > getCoords().x) //S� confere as coordenadas do player quando o Big Eye est� no ch�o
			direita = true;
		else
			direita = false;

		if (timerAtaque >= 1)
		{
			//velVertical = 0;
			velVertical = -350.f;
			noChao = false;

			timerAtaque = 0;
		}
	}

	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void BigEye::executar(float dt)
{
	mover(dt);

	if (!noChao)
		sofrerAcaoDaGravidade(dt);
	
}

void BigEye::danificar(Megaman* p)
{
	p->machucar(dano);
}

std::string BigEye::getTextureFile()
{
	if (nivel_maldade == 1)
	{
		if (direita)
			return "Sprites/Inimigos/BigEye1-blue-dir.png";
		return "Sprites/Inimigos/BigEye1-blue-esq.png";
	}
	else if (nivel_maldade == 2)
	{
		if (direita)
			return "Sprites/Inimigos/BigEye1-red-dir.png";
		return "Sprites/Inimigos/BigEye1-red-esq.png";
	}
	else
	{
		if (direita)
			return "Sprites/Inimigos/BigEye1-BAD-dir.png";
		return "Sprites/Inimigos/BigEye1-BAD-esq.png";
	}
}