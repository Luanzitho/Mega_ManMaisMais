#pragma once

#include "Ente.h"
#include "Jogo.h"

class Jogo;

class Menu: public Ente
{
private:
	Jogo* pJog;
	Gerenciador_Grafico* pG;

public:
	Menu();
	~Menu();
	void executar(float dt);
	void setGame(Jogo* jog);
	std::string getTextureFile();
	//void setDesenho(Gerenciador_Grafico* pG);
};