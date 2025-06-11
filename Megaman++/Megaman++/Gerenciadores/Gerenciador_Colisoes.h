#pragma once

#include "../Entidades/Personagens/Inimigo.h"
#include "../Entidades/Personagens/Megaman.h"
#include "../Entidades/Projeteis/Projetil.h"
#include "../Entidades/Projeteis/ProjetilMetall.h"
#include "../Entidades/Obstaculos/Obstaculo.h"
#include <vector>
#include <list>
#include <set>

class Gerenciador_Colisoes
{
private:
	std::vector<Inimigo*> LIs;
	std::list<Obstaculo*> LOs;
	std::set<Projetil*> LPs;
	Megaman* p1;

public:
	Gerenciador_Colisoes();
	~Gerenciador_Colisoes();
	const bool verificarColisao(Entidade* pe1, Entidade* pe2);
	void tratarColisaoMegaObstacs();
	void tratarColisaoMegaInimigos();
	void tratarColisaoMegaProjeteis();
	void tratarColisaoInimsProjeteis();
	void tratarColisaoInimsObstacs();
	void tratarColisaoProjObstacs();
	void tratarColisaoProjLimites();
	void incluirInimigo(Inimigo* pI);
	void incluirObstaculo(Obstaculo* pO);
	void incluirProjetil(Projetil* pP);
	void incluirMegaman(Megaman* pM);
	void executar();
};

