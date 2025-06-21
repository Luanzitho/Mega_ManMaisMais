#pragma once
#include "Obstaculo.h"

class Mola : public Obstaculo
{
private:
	float elasticidade; // For�a da mola

public:
	Mola();
	~Mola();
	void executar(float dt);
	void obstaculizar(Personagem* pPers);
	std::string getTextureFile();
	void salvar();
};

