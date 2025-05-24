#pragma once
#include <vector>
#include <list>
#include <set>
using namespace::std;
//#include <SFML/Graphics.hpp>
//using namespace::sf;

class Gerenciador_Colisoes
{
private:
	vector<Inimigo*> LIs;
	list<Obstaculo*> LOs;
	set<Projetil*> LPs;
	Jogador* pJog1;
	//(...)

public:
	const bool verificarColisao();

};

