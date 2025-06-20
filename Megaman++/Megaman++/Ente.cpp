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

void Ente::setId(const int id)
{
	this->id = id;
}

bool Ente::operator==(int id) const
{
	if (this->id == id)
		return true;
	return false;
}

const int Ente::getId()
{
	return id;
}

const sf::Vector2f Ente::getTamanho() { return tamanho; }

void Ente::setTamanho(const sf::Vector2f size) { tamanho = size; }

const sf::Vector2f Ente::getCoords() { return coords; }

void Ente::setCoords(const sf::Vector2f coordenadas) { coords = coordenadas; }

void Ente::desenhar() { pGG->desenharEnte(this); }
