#pragma once

#include "Ente.h"
#include "Menu.h"
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Megaman.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Listas/ListaEntidades.h"
#include "Entidades/Personagens/Metall.h"

class Jogo
{
private:
	Megaman* pJog1;
	Gerenciador_Grafico GG;
	Megaman* p1, *p2;
	Metall* m1;
	ListaEntidades* LEs;
	bool inMenu;
	bool playing;

public:
	Jogo();
	~Jogo();
	void executar();
	Gerenciador_Grafico* getGerenciador();
};