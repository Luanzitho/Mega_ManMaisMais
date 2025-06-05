#include "Megaman.h"
#include "Metall.h"
#include <iostream>

Megaman::Megaman() : Personagem(5), pontos(0), noChao(false), direita(true), gravidade(300), velocidade(0), aceleracao(100.f), velVertical(0), velMax(200), player1(true)
{
	LE = nullptr;
}

Megaman::Megaman(bool player) : Personagem(5), pontos(0), noChao(false), direita(true), gravidade(300), velocidade(0), aceleracao(100.f), velVertical(0), velMax(200), player1(player)
{
	LE = nullptr;
}

Megaman::~Megaman(){}

void Megaman::associaListaEntidades(ListaEntidades* lista)
{
	LE = lista;
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

	if (!noChao) //Confere se ele está no chão, se sim, consegue pular, se não, sofre efeito da gravidade
		velVertical += gravidade * dt;
	else
	{
		velVertical = 0;

		if (player1) //Se for Player 1 usa seta para cima, se não, usa W
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				velVertical = -300.f;
				noChao = false;
				std::cout << "Tenho " << num_vidas << " de HP" << std::endl;
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
	
	posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	if (posicao.y + getTamanho().y >= 600)
	{
		posicao.y = 600 - getTamanho().y;
		noChao = true;
	}

	setCoords(posicao);
}

void Megaman::atirar(float dt)
{
	if (player1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			sf::Vector2f pos = getCoords();

			ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
			LE->incluirEntidade(tiro);
			tiro->setGerenciadorGrafico(pGG);
		}
	}

	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			sf::Vector2f pos = getCoords();

			ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
			LE->incluirEntidade(tiro);
			tiro->setGerenciadorGrafico(pGG);
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