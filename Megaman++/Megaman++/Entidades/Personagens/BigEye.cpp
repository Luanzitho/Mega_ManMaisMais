#include "BigEye.h"

BigEye::BigEye() : gravidade(300), velMax(50), aceleracao(150), timerAtaque(0)
{
	setNumVidas(20);

	setTamanho(sf::Vector2f(80.f, 100.f));
}

BigEye::~BigEye()
{
}

void BigEye::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	sf::Vector2f alvo = pMega->getCoords();

	timerAtaque += dt; //Quando o timer atinge 3.5 o BigEye pode pular
	
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

	//posicao.x += velocidade * dt;
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
	return "Sprites/Inimigos/BigEye1-blue.png";
}