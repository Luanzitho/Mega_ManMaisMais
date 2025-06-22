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
	void obstaculizar(Personagem* pPers);
	std::string getTextureFile();
	const float getAltura();
	void salvar();
	void carregar();
};

