#pragma once

#include "../Ente.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"

class Fase:public Ente
{
private:
	Gerenciador_Colisoes* GC;

public:
	Fase();
	~Fase();
	virtual void executar();
	void gerenciarColisoes();
	void criarInimigosFaceis();
	void criarPlataformas();

	virtual void criarInimigos() = 0;
	virtual void criarObstaculos() = 0;
	void criarCenario();
};

