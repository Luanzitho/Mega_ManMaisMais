#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
//#include "Gerenciadores/Gerenciador_Colisoes.h"
#include <string>
#include <fstream>
#include "json.hpp"

using namespace nlohmann;
class Gerenciador_Grafico;

class Ente
{
protected:
	int id;
	Gerenciador_Grafico* pGG;
	//Gerenciador_Colisoes* pGC;
	sf::Vector2f coords;
	sf::Vector2f tamanho;
	static json dadosSalvos;
	/*static int qualEnte1;
	static int qualEnte2;
	static int qualEnte3;
	static int qualEnte4;
	static int qualEnte5;
	static int qualEnte6;
	static int qualEnte7;
	static int qualEnte8;
	static int qualEnte9;
	static int qualEnte10;
	static int qualEnte11;*/
	

public:
	Ente();
	Ente(sf::Vector2f coordsIni, sf::Vector2f size);
	~Ente();
	void setGerenciadorGrafico(Gerenciador_Grafico* p);
	//void setGerenciadorColisoes(Gerenciador_Colisoes* p);
	void setId(const int id);
	bool operator==(int id) const;
	const int getId();
	virtual void executar(float dt) = 0;
	virtual std::string getTextureFile() = 0;
	const sf::Vector2f getTamanho();
	void setTamanho(const sf::Vector2f size);
	const sf::Vector2f getCoords(); 
	void setCoords(const sf::Vector2f coordenadas);
	void desenhar();
	virtual void salvar();
};