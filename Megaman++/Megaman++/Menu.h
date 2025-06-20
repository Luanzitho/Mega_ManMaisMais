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
	int escolha, tela, fase;
	bool isPressed, enter, start;
	bool pause;
	sf::Font* font;
	std::vector<const char*> options, optionsPause;
	std::vector<sf::Text> texts, textsPause;
	std::vector<sf::Vector2f> coordsTexts;
	float cooldown;
	

public:
	Menu();
	~Menu();
	void executar(float dt);
	void setGame(Jogo* jog);
	std::string getTextureFile();
	int getEscolha() { return escolha; };
	void selecionar();
	void desenhaInteracao();
	void setPause(bool pausado);
};