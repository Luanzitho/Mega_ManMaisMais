#include "BigEye.h"

BigEye::BigEye() : aceleracao(150), timerAtaque(0)
{
	setTamanho(sf::Vector2f(80.f, 100.f));

	velMax = 50;

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

	if (!noChao) //Só se movimenta se estiver no ar
	{
		velVertical += gravidade * dt;
		
		if (direita)
			velocidade += velMax;
		else
			velocidade -= velMax;

		posicao.x += velocidade * dt;
	}

	else //Se estiver no chão, procura o player e pula se o timer estiver em 3.5
	{
		timerAtaque += dt; //Quando o timer atinge 3.5 o BigEye pode pular

		velocidade = 0;

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

	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void BigEye::executar(float dt)
{
	mover(dt);
}

void BigEye::danificar(Megaman* p)
{
	p->machucar(4);
}

std::string BigEye::getTextureFile()
{
	if(nivel_maldade==1)
		return "Sprites/Inimigos/BigEye1-blue.png";

	else if (nivel_maldade == 2)
		return "Sprites/Inimigos/BigEye1-red.png";

	else
		return "Sprites/Inimigos/BigEye1-BAD.png";
}