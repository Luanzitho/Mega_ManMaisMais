#include "Megaman.h"
#include "Metall.h"

Megaman::Megaman() : Personagem(5), pontos(0), noChao(false), gravidade(50), velocidade(0), aceleracao(30.f), velVertical(0), velMax(100), player1(true)
{
}

Megaman::Megaman(bool player) : Personagem(5), pontos(0), noChao(false), gravidade(50), velocidade(0), aceleracao(30.f), velVertical(0), velMax(100), player1(player)
{
}

Megaman::~Megaman(){}

void Megaman::mover(float dt)
{
	sf::Vector2f posicao = getCoords();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocidade -= aceleracao * dt;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocidade += aceleracao * dt;

	else
		velocidade = velocidade * 0.7;
	
	if (velocidade > velMax)
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);

	if (!noChao)
		velVertical += gravidade * dt;
	else
	{
		velVertical = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			velVertical = -100.f;
			noChao = false;
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

void Megaman::executar(float dt) 
{
	mover(dt);
	//atirar();
}

std::string Megaman::getTextureFile() 
{
	if(player1)
		return "Sprites/Megaman/Parado/Parado1.png";
	else
		return "Sprites/Megaman/Parado/Parado2.png";
}