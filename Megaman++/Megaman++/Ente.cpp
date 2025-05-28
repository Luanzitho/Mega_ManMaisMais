#include "Ente.h"

Ente::Ente(): id(contId++)
{
	pGG = new Gerenciador_Grafico();
}
int Ente::contId(0);

Ente::~Ente()
{
}
/*
void Ente::setTexturaTESTE()
{
	if (!textura.loadFromFile("Sprites/Megaman/Parado/Parado1.png")) {
		std::cout << "Erro ao carregar textura!" << std::endl;
	}
	else {
		std::cout << "Textura carregada com sucesso!" << std::endl;
	}
	//textura.loadFromFile("Sprites/Megaman/Parado/Parado1.png");
}

sf::Texture* Ente::getTexturaTESTE()
{
	return &textura;
}

sf::Sprite Ente::getSprite()
{
	return sprite;
}
*/
void Ente::desenhar()
{
	pGG->desenharEnte(this);
}
