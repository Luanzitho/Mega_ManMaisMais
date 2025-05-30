#include <SFML/Graphics.hpp>

#include "Jogo.h"
#include "Ente.h"
#include "Entidades/Entidade.h"
#include "Entidades/Personagens/Megaman.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Listas/ListaEntidades.h"
#include "Entidades/Personagens/Metall.h"

int main()
{
    //Jogo jog;
    //jog.executar();

    //ListaEntidades* LEs;
    //LEs = new ListaEntidades();

    //TESTE MEGAMAN
    Megaman* p1;
    Megaman* p2;
    p1 = new Megaman(true);
    p2 = new Megaman(false);
    Metall* m1;
    m1 = new Metall();

    Gerenciador_Grafico* GG = Gerenciador_Grafico::getInstancia();

    p1->setCoords(sf::Vector2f(550.f, 180.f));
    p1->setTamanho(sf::Vector2f(70.f, 70.f));
    m1->setCoords(sf::Vector2f(100.f, 400.f));
    m1->setTamanho(sf::Vector2f(50.f, 50.f));
    
    //LEs->incluirEntidade(p1); //A LISTA AINDA ESTÁ COM PROBLEMAS, INUTILIZAVEL POR ENQUANTO


    p2->setCoords(sf::Vector2f(950.f, 180.f));
    p2->setTamanho(sf::Vector2f(100.f, 100.f));

    while (GG->janelaEstaAberta())
    {
        GG->fecharJanela();
        GG->limparJanela();
        
        GG->desenharEnte(static_cast<Ente*>(p1));
        GG->desenharEnte(static_cast<Ente*>(p2));
        p1->executar();
        p2->executar();
        GG->desenharEnte(static_cast<Ente*>(m1));

        GG->mostrarConteudoJanela();
    }
   
    return 0;
}