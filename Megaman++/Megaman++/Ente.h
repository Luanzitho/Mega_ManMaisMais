#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
#include <string>

class Gerenciador_Grafico;

class Ente
{
protected:
	int id;
	static int contId;
	Gerenciador_Grafico* pGG;
	sf::Vector2f coords;
	sf::Vector2f tamanho;

public:
	Ente();
	Ente(sf::Vector2f coordsIni, sf::Vector2f size);
	~Ente();
	void setGerenciadorGrafico(Gerenciador_Grafico* p);
	virtual void executar() = 0;
	virtual std::string getTextureFile() = 0;
	const sf::Vector2f getTamanho(); //TESTE
	void setTamanho(sf::Vector2f size);
	const sf::Vector2f getCoords(); 
	void setCoords(sf::Vector2f coordenadas); //TESTE
	void desenhar();
};