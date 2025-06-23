#include "Ente.h"
#include <iostream>

Ente::Ente(): id(0), indiceAtual(0)
{
	pGG = nullptr;
	std::fstream jsonFile("Saves/save1.json");
	if(jsonFile.is_open() && dadosSalvos== nullptr)
	{
		jsonFile >> dadosSalvos;
		jsonFile.close();
	}
	else if(!jsonFile.is_open())
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
json Ente::dadosSalvos; // Inicializa o objeto JSON vazio

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

void Ente::carregar()
{
	int lugar = getId();
	//carregando os atributos de Ente dos dados salvos
	setCoords(sf::Vector2f(dadosSalvos["id"][lugar][indiceAtual]["posicao"]["x"], dadosSalvos["id"][lugar][indiceAtual]["posicao"]["y"]));
	setTamanho(sf::Vector2f(dadosSalvos["id"][lugar][indiceAtual]["tamanho"]["x"], dadosSalvos["id"][lugar][indiceAtual]["tamanho"]["y"]));

}
