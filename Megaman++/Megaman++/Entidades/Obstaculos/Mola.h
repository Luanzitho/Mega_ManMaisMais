#pragma once
#include "Obstaculo.h"

class Mola : public Obstaculo
{
private:
	float elasticidade; // Força da mola
	static int indiceMola;

public:
	Mola();
	~Mola();
	void executar(float dt);
	void obstaculizar(Entidade* pEnti);
	std::string getTextureFile();
	void salvar();
	void carregar();
	static void resetIndice() { indiceMola = -1; }
};

