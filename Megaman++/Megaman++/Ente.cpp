#include "Ente.h"
#include <iostream>

Ente::Ente(): id(0)
{
	pGG = nullptr;
	std::fstream jsonFile("Saves/save1.json");
	if(jsonFile.is_open())
	{
		jsonFile >> dadosSalvos;
		jsonFile.close();
	}
	else
	{
		std::cout << "criando novo arquivo..." << std::endl;

		std::ofstream novoArquivo("Saves/save1.json");
		if (novoArquivo.is_open()) {
			dadosSalvos["mensagem"] = "Arquivo JSON criado automaticamente.";
			novoArquivo << dadosSalvos.dump(4);
			novoArquivo.close();
			std::cout << "Arquivo JSON criado com sucesso!" << std::endl;
		}
		else {
			std::cout << "Erro ao criar o arquivo JSON!" << std::endl;
		}
	}
	
	//pGC = nullptr;
}
json Ente::dadosSalvos = json::object(); // Inicializa o objeto JSON vazio
/*int Ente::qualEnte1 = 0;
int Ente::qualEnte2 = 0;
int Ente::qualEnte3 = 0;
int Ente::qualEnte4 = 0;
int Ente::qualEnte5 = 0;
int Ente::qualEnte6 = 0;
int Ente::qualEnte7 = 0;
int Ente::qualEnte8 = 0;
int Ente::qualEnte9 = 0;
int Ente::qualEnte10 = 0;
int Ente::qualEnte11 = 0;*/

Ente::Ente(sf::Vector2f coordsIni, sf::Vector2f size): coords(coordsIni), tamanho(size), id(0)
{
	delete pGG;
	//pGC = nullptr;
}

Ente::~Ente()
{
	pGG = nullptr;
}

void Ente::setGerenciadorGrafico(Gerenciador_Grafico* p)
{
	pGG = p;
}

void Ente::setId(const int id)
{
	this->id = id;
}

const int Ente::getId()
{
	return id;
}
bool Ente::operator==(int id) const
{
	return this->id == id;
}

const sf::Vector2f Ente::getTamanho() { return tamanho; }

void Ente::setTamanho(const sf::Vector2f size) { tamanho = size; }

const sf::Vector2f Ente::getCoords() { return coords; }

void Ente::setCoords(const sf::Vector2f coordenadas) { coords = coordenadas; }

void Ente::desenhar() { pGG->desenharEnte(this); }

void Ente::salvar()
{
	int lugar = getId();


	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["posicao"]["x"] = getCoords().x;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["posicao"]["y"] = getCoords().y;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["tamanho"]["x"] = getTamanho().x;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["tamanho"]["y"] = getTamanho().y;
	/*if (lugar == 1)qualEnte1++;
	else if (lugar == 2)qualEnte2++;
	else if (lugar == 3)qualEnte3++;
	else if (lugar == 4)qualEnte4++;
	else if (lugar == 5)qualEnte5++;
	else if (lugar == 6)qualEnte6++;
	else if (lugar == 7)qualEnte7++;
	else if (lugar == 8)qualEnte8++;
	else if (lugar == 9)qualEnte9++;
	else if (lugar == 10)qualEnte10++;
	else if (lugar == 11)qualEnte11++;
	//std::cout << "criando novo arquivo..." << std::endl;*/

	std::ofstream novoArquivo("Saves/save1.json");
	if (novoArquivo.is_open()) {
		novoArquivo << dadosSalvos.dump(4);
		novoArquivo.close();
		std::cout << "Arquivo JSON criado com sucesso!" << std::endl;
	}
	else {
		std::cout << "Erro ao criar o arquivo JSON!" << std::endl;
	}
}
