#include "Jogo.h"
#include "Entidades/Personagens/Megaman.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo(): GG(), inMenu(false), playing(true), p1(new Megaman), p2(new Megaman(false)), m1(new Metall)
{
	p1->setCoords(sf::Vector2f(550.f, 180.f));
	p1->setTamanho(sf::Vector2f(70.f, 70.f));
	m1->setCoords(sf::Vector2f(100.f, 400.f));
	m1->setTamanho(sf::Vector2f(50.f, 50.f));
	p2->setCoords(sf::Vector2f(950.f, 180.f));
	p2->setTamanho(sf::Vector2f(100.f, 100.f));
	LEs = new ListaEntidades();
	p1->setGerenciadorGrafico(&GG);
	p2->setGerenciadorGrafico(&GG);
	m1->setGerenciadorGrafico(&GG);
	LEs->incluirEntidade(static_cast <Entidade*>(p1));
	LEs->incluirEntidade(static_cast <Entidade*>(p2));
	LEs->incluirEntidade(static_cast <Entidade*>(m1));
}

Jogo::~Jogo()
{

}

void Jogo::executar()
{
	Menu* menu= new Menu;

	menu->setCoords(sf::Vector2f(550.f, 180.f));
	menu->setTamanho(sf::Vector2f(70.f, 70.f));
	menu->setGame(this);

	sf::Clock tempo;
	while (GG.janelaEstaAberta())
	{
		if (inMenu)
		{
			GG.fecharJanela();
			GG.limparJanela();
			GG.desenharEnte(static_cast<Ente*>(menu));
			//menu->executar();
		}
		else if (playing)
		{
			float dt = tempo.restart().asSeconds();

			GG.fecharJanela();
			GG.limparJanela();
			LEs->percorrer(dt);
			//GG.desenharEnte(static_cast<Ente*>(p1));
			//GG.desenharEnte(static_cast<Ente*>(p2));
			//p1->executar();
			//p2->executar();
			//GG.desenharEnte(static_cast<Ente*>(m1));
		}
		GG.mostrarConteudoJanela();
	}
}

Gerenciador_Grafico* Jogo::getGerenciador()
{
	return &GG;
}


