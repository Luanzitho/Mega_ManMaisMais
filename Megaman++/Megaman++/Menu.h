#pragma once

#include "Ente.h"
#include "Jogo.h"
#include <vector>

class Jogo;

class Menu : public Ente
{
private:
	Jogo* pJog;
	//Gerenciador_Grafico* pGG;
	int escolha, tela;
	bool isPressed, enter, start;
	sf::Font* font;
	std::vector<const char*> options;
	std::vector<sf::Text> texts;
	std::vector<sf::Vector2f> coordsTexts;
	

public:
	Menu();
	~Menu();
	void executar(float dt);
	void setGame(Jogo* jog);
	std::string getTextureFile();
	int getEscolha() { return escolha; };
	void selecionar();
	void desenhaInteracao();
};