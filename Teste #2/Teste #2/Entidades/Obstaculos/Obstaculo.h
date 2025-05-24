#pragma once
#include "../Entidade.h"
class Obstaculo:public Entidade
{
protected:
	bool danoso;
	//(...)

public:
	Obstaculo();
	~Obstaculo();
	virutal void executar() = 0;
	virtual void obstacular() = 0;
	//(...)
};

