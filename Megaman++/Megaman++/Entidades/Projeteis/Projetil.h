#pragma once

#include "../Entidade.h"
#include "../../Listas/ListaEntidades.h"

class Projetil:public Entidade
{
protected:
	bool ativo;
	int dano;
	float velocidade;
	ListaEntidades* LEs;

public:
	Projetil();
	~Projetil();
	void desativar();
	const bool getAtivo();
	void associaListaEntidades(ListaEntidades* pLista);
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
};

