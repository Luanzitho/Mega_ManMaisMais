#pragma once

#include "../Entidade.h"
#include "../Personagens/Personagem.h"

class Obstaculo:public Entidade
{
protected:
	bool danoso;

public:
	Obstaculo();
	~Obstaculo();
	virtual void executar() = 0;
	virtual void obstaculizar(Personagem* pPers) = 0;
	virtual std::string getTextureFile() = 0;
};

