#include "CutMan.h"

CutMan::CutMan(): cooldownNoChao(0), timerAtirar(0), timerPerseguir(0), timerPular(0)
{
	setTamanho(sf::Vector2f(80.f, 80.f));

	setNumVidas(22 + nivel_maldade * 2);

	velMax = 200;

	forca = 2 + nivel_maldade;
}

CutMan::~CutMan()
{
}

void CutMan::atirar()
{

}

void CutMan::mover(float dt)
{
	sf::Vector2f posicao = getCoords();
	sf::Vector2f alvo = pMega->getCoords();

	cooldownNoChao += dt;
	if (cooldownNoChao > 0.1 && noChao)
	{
		noChao = false;
		cooldownNoChao = 0;
	}

	if (noChao) 
	{
		timerPerseguir += dt;
		timerPular += dt;

		if (timerPerseguir >= 1) 
		{
			if (timerPular >= 3)
			{
				velVertical = -300;
				noChao = false;
				timerPular = 0;
			}

			if (alvo.x > posicao.x)
			{
				velocidade += velMax;
			}

			else
			{
				velocidade -= velMax;
			}

			timerPerseguir = 0;
		}
	}

	else
	{
		velVertical += gravidade * dt;
	}

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);

	posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void CutMan::executar(float dt)
{
	mover(dt);
}

#include <iostream>
void CutMan::danificar(Megaman* p)
{
	std::cout << "Colidiu!\n";
}

std::string CutMan::getTextureFile()
{
	return "Sprites/Inimigos/CutMan1-L.png";
}