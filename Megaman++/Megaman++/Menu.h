#pragma once

#include "Ente.h"
#include "Jogo.h"

class Jogo;

class Menu: public Ente
{
private:
	Jogo* pJog;

public:
	Menu();
	~Menu();
	void executar();
	void setGame(Jogo* jog);
	std::string getTextureFile();
	void setDesenho(Gerenciador_Grafico* pG);
};