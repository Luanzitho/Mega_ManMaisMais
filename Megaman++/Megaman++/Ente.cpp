#include "Ente.h"

Ente::Ente(): id(contId++)
{
	pGG = nullptr;
}
int Ente::contId(0);

Ente::Ente(sf::Vector2f coordsIni, sf::Vector2f size): coords(coordsIni), tamanho(size) {}

Ente::~Ente(){}

void Ente::setGerenciadorGrafico(Gerenciador_Grafico* p)
{
	pGG = p;
}

const sf::Vector2f Ente::getTamanho() { return tamanho; }

void Ente::setTamanho(sf::Vector2f size) { tamanho = size; }

const sf::Vector2f Ente::getCoords() { return coords; }

void Ente::setCoords(sf::Vector2f coordenadas) { coords = coordenadas; }

void Ente::desenhar() { pGG->desenharEnte(this); }
