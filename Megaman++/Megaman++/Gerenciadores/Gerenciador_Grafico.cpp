#include "Gerenciador_Grafico.h"
#include "../Entidades/Personagens/Megaman.h"
#include <iostream>

Gerenciador_Grafico* Gerenciador_Grafico::instancia = nullptr;

Gerenciador_Grafico::Gerenciador_Grafico(): window(sf::VideoMode(1280, 720), "Mega Man++", sf::Style::Titlebar | sf::Style::Close)
{
    window.setFramerateLimit(60);

    sf::Image icone;
    //icone.loadFromFile("Sprites/Menu/icone.png");

    if (!icone.loadFromFile("Sprites/Menu/icone.png"))
    {
        std::cout << "Falha ao carregar icone!" << std::endl;
    }

    window.setIcon(icone.getSize().x, icone.getSize().y, icone.getPixelsPtr());

    posicionarConsole(1700, 100); //Posiciona o console ao lado da janela do jogo

	texturaHpBar.loadFromFile("Sprites/Megaman/HPBar/HPBar.png");
	spriteHpBar.setTexture(texturaHpBar);
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
    //delete instancia;
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
            
            if (evento.text.unicode < 128 && evento.text.unicode >= 32) {
                std::cout << "entrou2" << std::endl;
                textoDigitado += static_cast<char>(evento.text.unicode);
            }

            // Se quiser, pode adicionar tratamento de Backspace:
            if (evento.text.unicode == 8 && !textoDigitado.empty()) { // 8 = Backspace
                textoDigitado.pop_back();
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

void Gerenciador_Grafico::desenharBarraVida(Ente* pE, float hp, sf::Vector2f posicao)
{
    float largura = 3;
	float altura = 3;

    int cont = 28 - hp;

    spriteHpBar.setTextureRect(sf::IntRect(0+8*cont, 0, 8, 56));

    spriteHpBar.setScale(largura, altura);
	spriteHpBar.setPosition(posicao.x, posicao.y + 50);

	window.draw(spriteHpBar);
}

void Gerenciador_Grafico::desenharPontos(int qtdPontos, sf::Vector2f posicao)
{
    sf::Font fonte;
    if (!fonte.loadFromFile("Fontes/Pixelify_Sans/static/PixelifySans-Regular.ttf"))
    {
        std::cout << "Erro ao carregar fonte de pontos!" << std::endl;
        return;
    }

    sf::Text textoPontos;
    textoPontos.setFont(fonte);
    textoPontos.setString("Pontos: " + std::to_string(qtdPontos));
    textoPontos.setCharacterSize(36);
    textoPontos.setFillColor(sf::Color::White);
    textoPontos.setPosition(posicao);
	window.draw(textoPontos);
}

std::string Gerenciador_Grafico::getTexto()
{
    return textoDigitado;
}

void Gerenciador_Grafico::limpaTexto()
{
    textoDigitado.clear();
}

void Gerenciador_Grafico::fecharJanela()
{
	window.close();
}

