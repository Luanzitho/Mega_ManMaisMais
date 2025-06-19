#pragma once

#include "../Entidade.h"
#include "../../Listas/ListaEntidades.h"

class Projetil:public Entidade
{
protected:
	bool doMega;
	const int dano;
	const float empuxo;
	const float velocidade;
	ListaEntidades* LEs;

public:
	Projetil();
	Projetil(const float vel, int dmg);
	~Projetil();
	const bool getDoMega();
	void associaListaEntidades(ListaEntidades* pLista);
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
};

