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
	//sf::Sprite sprite;
	sf::Texture textura;
	//char* nomeTextureFile;
	//sf::Vector2f coords;

public:
	Ente();
	~Ente();
	//void setTexturaTESTE(); //Apenas para fazer testes
	//sf::Texture* getTexturaTESTE(); //Apenas para fazer testes
	virtual void executar() = 0;
	//sf::Sprite getSprite();
	//virtual void setTextureFile() = 0;
	virtual std::string getTextureFile() = 0;
	void desenhar();
};