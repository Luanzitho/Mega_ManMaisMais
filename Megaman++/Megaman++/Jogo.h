#pragma once

#include "Ente.h"
#include "Menu.h"
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Megaman.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Listas/ListaEntidades.h"
#include "Entidades/Personagens/Metall.h"
#include "Entidades/Personagens/BigEye.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Obstaculos/Plataforma.h"
#include "Entidades/Obstaculos/Espinho.h"

class Jogo
{
private:
	Gerenciador_Colisoes GC;
	Gerenciador_Grafico& GG;
	Megaman* p1, *p2;
	Plataforma* pl1, *pl2, *pl3;
	Metall* m1;
	Espinho* es;
	BigEye* m2;
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