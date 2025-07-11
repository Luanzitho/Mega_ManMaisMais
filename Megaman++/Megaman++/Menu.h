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
	
	int escolha, tela, fase, pontuacao;
	bool isPressed, enter, start;
	bool pause, terminou;
	sf::Font* font;
	std::vector<const char*> options;
	std::vector<sf::Text> texts;
	std::vector<sf::Text> ranking;
	std::vector<sf::Vector2f> coordsTexts;
	float cooldown;
	std::vector<std::string> rankingNomes;
	std::vector<int> rankingPontos;

	//int quantidadeMenus;
	

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
	void salvar();
	void carregar();
	void setTerminou(bool termi, int pontos);
	//void carregaRanking();
};