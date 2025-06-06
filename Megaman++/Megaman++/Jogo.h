#pragma once

#include "Ente.h"
#include "Menu.h"
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Megaman.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Listas/ListaEntidades.h"
#include "Entidades/Personagens/Metall.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"

class Jogo
{
private:
	Gerenciador_Colisoes GC;
	Gerenciador_Grafico& GG;
	Megaman* p1, *p2;
	Metall* m1;
	ListaEntidades* LEs;
	bool inMenu;
	bool playing;
	int faseA;

public:
	Jogo();
	~Jogo();
	void executar();
	void iniciar(int fase);
	void encerrar();
	Gerenciador_Grafico* getGerenciador();
};