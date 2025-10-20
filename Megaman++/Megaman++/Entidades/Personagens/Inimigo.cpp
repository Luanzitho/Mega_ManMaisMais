#include "Inimigo.h"

Inimigo::Inimigo() : pMega(nullptr), dano(0), LE(nullptr), GC(nullptr)
{
	srand(time(NULL));

	//setId(2);

	nivel_maldade = rand() % 3 + 1;

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