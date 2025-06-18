#include "Ente.h"

Ente::Ente(): id(0)
{
	pGG = nullptr;
	//pGC = nullptr;
}

Ente::Ente(sf::Vector2f coordsIni, sf::Vector2f size): coords(coordsIni), tamanho(size), id(0) 
{
	delete pGG;
	//pGC = nullptr;
}

Ente::~Ente()
{
	pGG = nullptr;
}

void Ente::setGerenciadorGrafico(Gerenciador_Grafico* p)
{
	pGG = p;
}

/*void Ente::setGerenciadorColisoes(Gerenciador_Colisoes* p)
{
	pGC = p;
}*/

void Ente::setId(int id)
{
	this->id = id;
}

int Ente::getId()
{
	return id;
}

const sf::Vector2f Ente::getTamanho() { return tamanho; }

void Ente::setTamanho(sf::Vector2f size) { tamanho = size; }

const sf::Vector2f Ente::getCoords() { return coords; }

void Ente::setCoords(sf::Vector2f coordenadas) { coords = coordenadas; }

void Ente::desenhar() { pGG->desenharEnte(this); }
