#include "Megaman.h"
#include "Metall.h"
#include <iostream>

Megaman::Megaman() : Personagem(20), pontos(0), direita(true), velMax(200), gravidade(300), /*aceleracao(100),*/ cooldownTiro(0.25), tempoCooldown(0), player1(true), cooldownNoChao(0)
{
	LE = nullptr;
	setId(1);

	setTamanho(sf::Vector2f(70.f, 70.f));
}

Megaman::Megaman(bool player) : Personagem(20), pontos(0), direita(true), velMax(200), gravidade(300), /*aceleracao(100),*/ cooldownTiro(0.25), tempoCooldown(0), player1(player), cooldownNoChao(0)
{
	LE = nullptr;
	setId(1);
}

Megaman::~Megaman(){}

void Megaman::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Megaman::mover(float dt)
{
	sf::Vector2f posicao = getCoords();

	if (player1) //Player 1 usa as SETAS
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocidade -= velMax; //aceleracao * dt;
			direita = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocidade += velMax; //aceleracao* dt;
			direita = true;
		}
		else
			velocidade = velocidade * 0.9;
	}

	else //Player 2 usa WASD
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocidade -= velMax; //aceleracao * dt;
			direita = false;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocidade += velMax; //aceleracao* dt;
			direita = true;
		}

		else
			velocidade = velocidade * 0.9;
	}

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);
	cooldownNoChao += dt;
	if (cooldownNoChao > 0.1 && noChao)// reseta a colisão do chão em um determinado tempo
	{
		noChao = false;
		cooldownNoChao = 0;
	}
	if (noChao) //Confere se ele está no chão, se sim, consegue pular, se não, sofre efeito da gravidade
	{
		velVertical = 0;

		if (player1) //Se for Player 1 usa seta para cima, se não, usa W
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				velVertical = -300.f;
				noChao = false;
				std::cout << "Tenho " << getNumVidas() << " de HP" << std::endl;
				std::cout << "FPS: " << 1.0 / dt << std::endl;
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				velVertical = -300.f;
				noChao = false;
			}
		}
	}

	else
	{
		velVertical += gravidade * dt;
	}

	posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void Megaman::atirar(float dt)
{
	tempoCooldown += dt;

	if (player1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (tempoCooldown >= cooldownTiro)
			{
				sf::Vector2f pos = getCoords();

				ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
				LE->incluirEntidade(tiro);
				//pGC->incluirProjetil(tiro);
				tiro->associaListaEntidades(LE);
				tiro->setGerenciadorGrafico(pGG);
				//tiro->setGerenciadorColisoes(pGC);

				tempoCooldown = 0;
			}
		}
	}

	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			if (tempoCooldown >= cooldownTiro)
			{
				sf::Vector2f pos = getCoords();

				ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
				LE->incluirEntidade(tiro);
				tiro->setGerenciadorGrafico(pGG);

				tempoCooldown = 0;
			}
		}
	}
}

void Megaman::executar(float dt)
{
	mover(dt);
	atirar(dt);
}

std::string Megaman::getTextureFile() 
{
	if(player1)
		return "Sprites/Megaman/Parado/Parado1.png";
	else
		return "Sprites/Megaman/Parado/Parado2.png";
}