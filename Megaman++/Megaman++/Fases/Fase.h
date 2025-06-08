#pragma once

#include "../Ente.h"
#include "../Listas/ListaEntidades.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"

class Fase:public Ente
{
private:
	Gerenciador_Colisoes* GC;
	ListaEntidades* listaEnts;

public:
	Fase();
	~Fase();
	virtual void executar() = 0;
	void gerenciarColisoes();
	void criarInimigosFaceis();
	void criarPlataformas();

	virtual void criarInimigos() = 0;
	virtual void criarObstaculos() = 0;
	void criarCenario();
};

