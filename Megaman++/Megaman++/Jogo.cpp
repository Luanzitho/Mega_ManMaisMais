#include "Jogo.h"
#include "Entidades/Personagens/Megaman.h"
#include <SFML/Graphics.hpp>

Jogo::Jogo() : GG(*Gerenciador_Grafico::getInstancia()), inMenu(false), playing(true), p1(new Megaman), p2(new Megaman(false)), m1(new Metall), m2(new BigEye), pl1(new Plataforma), es(new Espinho), faseA(0)
{
	p1->setCoords(sf::Vector2f(550.f, 180.f));
	
	m1->setCoords(sf::Vector2f(850.f, 550.f));
	
	p2->setCoords(sf::Vector2f(950.f, 180.f));
	
	m2->setCoords(sf::Vector2f(110.f, 530.f));

	pl1->setCoords(sf::Vector2f(10.f, 680.f));

	es->setCoords(sf::Vector2f(950.f, 600.f));

	LEs = new ListaEntidades();
	p1->setGerenciadorGrafico(&GG);
	p2->setGerenciadorGrafico(&GG);
	m1->setGerenciadorGrafico(&GG);
	m2->setGerenciadorGrafico(&GG);
	pl1->setGerenciadorGrafico(&GG);
	es->setGerenciadorGrafico(&GG);
	LEs->incluirEntidade(static_cast <Entidade*>(p1));
	//LEs->incluirEntidade(static_cast <Entidade*>(p2));
	LEs->incluirEntidade(static_cast <Entidade*>(m1));
	LEs->incluirEntidade(static_cast <Entidade*>(m2));
	LEs->incluirEntidade(static_cast <Entidade*>(pl1));
	LEs->incluirEntidade(static_cast <Entidade*>(es));

	m1->conhecerJogador(p1);
	m2->conhecerJogador(p1);

	p1->associaListaEntidades(LEs); //Teste da função atirar
	//p2->associaListaEntidades(LEs);

	GC.incluirMegaman(p1);
	GC.incluirInimigo(m1);
	GC.incluirInimigo(m2);
	GC.incluirObstaculo(pl1);
	GC.incluirObstaculo(es);
}

Jogo::~Jogo()
{
	encerrar();
}

void Jogo::executar()
{
	Menu* menu = new Menu();

	menu->setCoords(sf::Vector2f(0.f, 0.f));
	menu->setTamanho(sf::Vector2f(1280.f, 720.f));
	menu->setGame(this);
	//menu->setGerenciadorGrafico(&GG);

	sf::Clock tempo;
	float dt;

	while (GG.janelaEstaAberta())
	{
		dt = tempo.restart().asSeconds();
		GG.eventoFecharJanela();
		GG.limparJanela();
		if (inMenu)
			menu->executar(dt);
		else if (playing)
		{
			if(faseA==1)
			{
			
			}
			else if(faseA==2)
			{
			
			}
			GC.executar();
			
			LEs->percorrer(dt);
		}
		GG.mostrarConteudoJanela();
	}
}

void Jogo::iniciar(int fase)
{
	if(inMenu)
	{
		inMenu = false;
		playing = true;
		faseA = fase;
	}
}


void Jogo::encerrar()
{
	//LEs->limparLista();
	//delete LEs;

}

Gerenciador_Grafico* Jogo::getGerenciador()
{
	return &GG;
}
