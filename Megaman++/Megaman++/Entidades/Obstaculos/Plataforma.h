#pragma once

#include "Obstaculo.h"

class Plataforma:public Obstaculo
{
private:
	float altura;
	static int indicePlataforma;

public:
	Plataforma();
	~Plataforma();
	void executar(float dt);
	void obstaculizar(Entidade* pEnti);
	std::string getTextureFile();
	const float getAltura();
	void salvar();
	void carregar();
	static void resetIndice() { indicePlataforma = -1; }
};

