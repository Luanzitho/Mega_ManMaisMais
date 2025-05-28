#include "Jogo.h"

Jogo::Jogo(): GG()
{
	
}

Jogo::~Jogo()
{

}

void Jogo::executar()
{
	Menu menu;

	menu.setGame(this);
	menu.setDesenho(GG.getGerenciador_Grafico());
	menu.executar();

}


