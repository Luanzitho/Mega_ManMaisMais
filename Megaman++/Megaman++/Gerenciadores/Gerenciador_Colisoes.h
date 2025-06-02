#pragma once

#include "../Entidades/Personagens/Inimigo.h"
#include "../Entidades/Personagens/Megaman.h"
#include "../Entidades/Projetil.h"
//#include "../Entidades/Obstaculos/Obstaculo.h"
#include <vector>
#include <list>
#include <set>

class Gerenciador_Colisoes
{
private:
	std::vector<Inimigo*> LIs;
	//std::list<Obstaculo*> LOs;
	std::set<Projetil*> LPs;
	Megaman* p1;

public:
	Gerenciador_Colisoes();
	~Gerenciador_Colisoes();
	const bool verificarColisao(Entidade* pe1, Entidade* pe2);
	void colisaoJogsObstacs();
	void colisaoJogsInimigos();
	void colisaoJogsProjeteis();
	void colisaoInimsProjeteis();
	void incluirInimigo(Inimigo* pI);
	//void incluirObstaculo(Obstaculo* pO);
	void incluirProjetil(Projetil* pP);
	void executar();
};

