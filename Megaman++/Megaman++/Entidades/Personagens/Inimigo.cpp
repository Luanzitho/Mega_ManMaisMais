#include "Inimigo.h"
#include "../../Gerenciadores/Gerenciador_Colisoes.h"
#include <iostream>

Inimigo::Inimigo() : pMega(nullptr), dano(0), LE(nullptr), GC(nullptr)
{
	srand(time(NULL));

	//setId(2);
	std::mt19937 gen(rd()); //Motor aleatório (Mersenne Twister)
	
	nivel_maldade = std::uniform_int_distribution<>(1, 3)(gen); //Nível de maldade entre 1 e 3

	qtdPontos = nivel_maldade * 100; //Cada nível de maldade do inimigo resulta em 100 pontos a mais para a quantidade padrão de pontos

	pGS->carregarEfeito("EnemyDMG", "Sound/Effects/enemydmg.wav");
	pGS->carregarEfeito("Defeat", "Sound/Effects/defeat.wav");
	pGS->setVolumeEfeitos(100.f);
}
int Inimigo::qualInimigo = 0;

Inimigo::~Inimigo()
{
	LE = nullptr;
	GC = nullptr;
	pMega = nullptr;
}

void Inimigo::conhecerJogador(Megaman* p)
{
	pMega = p;
}

void Inimigo::machucar(const int dmg)
{
	num_vidas = num_vidas - dmg;
	pGS->tocarEfeito("EnemyDMG");

	if (num_vidas <= 0)
	{
		cederPontos();
		droparItem();
		destruir();

		if (id == 8) //Som de derrota para o CutMan
		{
			pGS->tocarEfeito("Defeat");
			//std::cout << "CutMan derrotado!\n";
		}
	}
}

void Inimigo::cederPontos()
{
	(*pMega) += qtdPontos;
}

void Inimigo::droparItem()
{
	if (!LE || !GC) {
        std::cerr << "droparItem: LE ou GC nulo. Não foi possível adicionar item.\n";
        return;
    }

    std::mt19937 gen(rd());
    int chance = std::uniform_int_distribution<>(1, 100)(gen); //1 a 100

    if (chance <= 30) //30% de chance
    {
        Regen* item = new Regen;
        sf::Vector2f pos = getCoords();
        //pos.y += 10.f;
        item->setCoords(pos);
        item->setGerenciadorGrafico(pGG);
        item->associaListaEntidades(LE);
        item->associaGerenciadorColisoes(GC);

        LE->incluirEntidade(item);
        GC->incluirItem(item);

        //std::cout << "Item dropado em (" << pos.x << "," << pos.y << "), chance=" << chance << "\n";
    }
    //else
    //{
    //    std::cout << "Sem drop (chance=" << chance << ")\n";
    //}
}

void Inimigo::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Inimigo::associaGerenciadorColisoes(Gerenciador_Colisoes* gc)
{
	GC = gc;
}

void Inimigo::salvar()
{
	int lugar = getId();
	if (lugar < 0 || lugar >= dadosSalvos["id"].size())
	{
		//std::cerr << "Erro: ID do inimigo fora dos limites do vetor de dados salvos." << std::endl;
		return;
	}
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["qtdPontos"] = qtdPontos;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["nivel_maldade"] = nivel_maldade;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["dano"] = dano;

	Personagem::salvar();
}

void Inimigo::carregar()
{
	int lugar = getId();
	qtdPontos = dadosSalvos["id"][lugar][indiceAtual]["qtdPontos"];
	nivel_maldade = dadosSalvos["id"][lugar][indiceAtual]["nivel_maldade"];
	dano = dadosSalvos["id"][lugar][indiceAtual]["dano"];

	Personagem::carregar();
}