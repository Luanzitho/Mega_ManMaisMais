#include "Megaman.h"

Megaman::Megaman() : Personagem(5), pontos(0), player1(true)//Define que o player tem 5 vidas ou uma barra de vida com 5 unidades
{
}

Megaman::Megaman(bool player) : Personagem(5), pontos(0), player1(player)
{
}

Megaman::~Megaman()
{
}

void Megaman::mover()
{
	if (player1) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			coords.x -= 0.1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			coords.x += 0.1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			coords.y -= 0.1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			coords.y += 0.1;
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			coords.x -= 0.1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			coords.x += 0.1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			coords.y -= 0.1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			coords.y += 0.1;
	}
}

void Megaman::executar() 
{
	mover();
	//atirar();
}

std::string Megaman::getTextureFile() 
{
	if(player1)
		return "Sprites/Megaman/Parado/Parado1.png";
	else
		return "Sprites/Megaman/Parado/Parado2.png";
}