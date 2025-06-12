#pragma once

#include "../Ente.h"
#include "../Listas/ListaEntidades.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Entidades/Personagens/BigEye.h"
#include "../Entidades/Personagens/Metall.h"

#include <fstream>
#include <vector>
#include "../json.hpp"

using namespace nlohmann;

class Fase:public Ente
{
private:
	
protected:
	Gerenciador_Colisoes GC;
	json faseJson;
	std::vector<int> tilesGid;
	sf::Texture imagemTiles;
	std::vector<sf::IntRect> tilesRects;
	//std::vector<sf::Texture> tilesTextures;
	sf::Texture* tilesAtual;
	int tileWidth;
	int columns;
	int tileCount;
	Megaman* p1;
	Metall* met; //A REMOVER
	BigEye* big; //A REMOVER
	std::vector<Plataforma*> plataformas;
	//std::vector<Metall*> metalls;
	//std::vector<Espinho*> espinhos;
	//std::vector<BigEye*> bigEyes;
	ListaEntidades* LEs;

public:
	Fase();
	~Fase();
	virtual void executar(float dt) = 0;
	void gerenciarColisoes();
	void criarInimigosFaceis();
	void criarPlataformas();
	virtual void criarInimigos() = 0;
	virtual void criarObstaculos() = 0;
	void desenharCenario();
	void separaSprites();
	std::string getTextureFile();
	//sf::Texture recortarTextura(const sf::Texture& original, sf::IntRect recorte);
	//virtual std::string getMapaFase()=0;

};

