#include "Menu.h"

Menu::Menu()
{
	pJog = nullptr;
}

Menu::~Menu()
{
}

void Menu::executar()
{
	desenhar();
}

void Menu::setGame(Jogo* jog)
{
	pJog = jog;
}

std::string Menu::getTextureFile()
{
	return "";
}

void Menu::setDesenho(Gerenciador_Grafico* pG)
{
	pGG = pG;
}
