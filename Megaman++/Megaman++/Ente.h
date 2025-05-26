#pragma once
#ifndef _ENTE_H_
#define _ENTE_H_

#include "Gerenciadores/Gerenciador_Grafico.h"
#include <string>

class Gerenciador_Grafico;

class Ente
{
protected:
	int id;
	static int contId;
	Gerenciador_Grafico* pGG;
	char nomeTextureFile[20];
	sf::Vector2f coords;

public:
	Ente();
	~Ente();
	virtual void executar() = 0;
	void desenhar();
};

#endif // _ENTE_H_