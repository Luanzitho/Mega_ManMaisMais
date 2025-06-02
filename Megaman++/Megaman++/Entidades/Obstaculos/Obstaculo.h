#pragma once

#include "../Entidade.h"

class Obstaculo:public Entidade
{
protected:
	bool danoso;

public:
	Obstaculo();
	~Obstaculo();
	virtual void executar() = 0;
	virtual void obstacular() = 0;
	virtual std::string getTextureFile() = 0;
};

