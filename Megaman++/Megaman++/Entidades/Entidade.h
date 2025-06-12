#pragma once

#include "../Ente.h"

class Entidade:public Ente
{
protected:
	bool vivo;
	float gravidade;
	//float x;
	//float y;
	//ostream buffer;

public:
	Entidade();
	~Entidade();
	void destruir();
	const bool getVivo();
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	//virtual void salvar() = 0;

	//void salvarDataBuffer(); 
};