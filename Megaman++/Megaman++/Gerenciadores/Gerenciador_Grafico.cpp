#include "Gerenciador_Grafico.h"
#include "../Entidades/Personagens/Megaman.h"
#include <iostream>

Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

Gerenciador_Grafico::Gerenciador_Grafico(): window(sf::VideoMode(1280, 720), "Mega Man++")
{
    window.setFramerateLimit(60);
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
    delete instancia;
}

Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() //Para instanciar um único Gerenciador_Grafico
{ 
    if (!instancia)
    {
        instancia = new Gerenciador_Grafico();
    }
    return instancia; 
}

sf::Texture& Gerenciador_Grafico::getTextura(const std::string& caminho) 
{
    auto it = texturas.find(caminho);
    
    if (it == texturas.end()) 
    {
        sf::Texture textura;
        textura.loadFromFile(caminho);
        texturas[caminho] = textura;
    }

    return texturas[caminho];
}

void Gerenciador_Grafico::desenharEnte(Ente* pE)
{
    if (!pE) return;

    sf::RectangleShape corpo;
    const std::string& caminho = pE->getTextureFile();
    sf::Texture& textura = getTextura(caminho);

    sf::Vector2f tam = pE->getTamanho();
    sf::Vector2f pos = pE->getCoords();

    corpo.setSize(tam);
    corpo.setPosition(pos);
    corpo.setTexture(&textura);

    window.draw(corpo);
}

bool Gerenciador_Grafico::janelaEstaAberta()
{
    return window.isOpen();
}

void Gerenciador_Grafico::eventoFecharJanela()
{
    sf::Event evento;

    while (window.pollEvent(evento)) 
    {
        if (evento.type == sf::Event::Closed) 
        {
            window.close();
        }

        
        // Captura as teclas digitadas (caracteres válidos)
        if (evento.type == sf::Event::TextEntered) {
            // Ignora teclas de controle (ex.: backspace, enter, etc)
            //std::cout << "entrou" << std::endl;
            if (evento.text.unicode < 128 && evento.text.unicode >= 32) {
                //std::cout << "entrou2" << std::endl;
                textoDigitado += static_cast<char>(evento.text.unicode);
            }

            // Se quiser, pode adicionar tratamento de Backspace:
            if (evento.text.unicode == 8 && !textoDigitado->empty()) { // 8 = Backspace
                textoDigitado->pop_back();
            }
        }
    }
}

void Gerenciador_Grafico::limparJanela()
{
    window.clear();
}

void Gerenciador_Grafico::mostrarConteudoJanela()
{
    window.display();
}

void Gerenciador_Grafico::desenhar(sf::Text text)
{
	window.draw(text);
}

void Gerenciador_Grafico::desenhar(sf::Sprite sprite)
{
    window.draw(sprite);
}

std::string Gerenciador_Grafico::digitar(std::string entradaUsuario)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        // Fecha a janela
        
        std::cout << "entrou" << std::endl;
        // Captura as teclas digitadas (caracteres válidos)
        if (event.type == sf::Event::TextEntered) {
            // Ignora teclas de controle (ex.: backspace, enter, etc)
            if (event.text.unicode < 128 && event.text.unicode >= 32) {
                entradaUsuario += static_cast<char>(event.text.unicode);
            }

            // Se quiser, pode adicionar tratamento de Backspace:
            if (event.text.unicode == 8 && !entradaUsuario.empty()) { // 8 = Backspace
                entradaUsuario.pop_back();
            }
        }
    }
    return entradaUsuario;
    // Atualiza o texto SFML com a string do usuário
    //texto.setString(entradaUsuario);
}

