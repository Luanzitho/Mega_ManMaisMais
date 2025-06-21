#include "Megaman.h"
#include "../../Gerenciadores/Gerenciador_Colisoes.h"

#include <iostream>

Megaman::Megaman() : Personagem(20), teclaApertada(false), cooldownTiro(0), player1(true), invencivel(false), framesInvencibilidade(0), cooldownNoChao(0)
{
	LE = nullptr;
	GC = nullptr;

	direita = true;

	setId(1);

	velMax = 200;

	setTamanho(sf::Vector2f(70.f, 70.f));
}
int Megaman::pontos(0);

Megaman::Megaman(bool player) : Personagem(20), teclaApertada(false), cooldownTiro(0), player1(player), invencivel(false), framesInvencibilidade(0), cooldownNoChao(0)
{
	LE = nullptr;
	GC = nullptr;

	setId(2);

	direita = true;

	velMax = 200;

	setTamanho(sf::Vector2f(70.f, 70.f));
}

Megaman::~Megaman()
{
	LE = nullptr;
	GC = nullptr;
}

void Megaman::associaListaEntidades(ListaEntidades* pLista)
{
	LE = pLista;
}

void Megaman::associaGerenciadorColisoes(Gerenciador_Colisoes* GC)
{
	this->GC = GC;
}

void Megaman::operator+=(const int pts)
{
	pontos = pontos + pts;
}

void Megaman::machucar(const int dmg)
{
	if (!invencivel)
		num_vidas = num_vidas - dmg;

	if (num_vidas <= 0)
		destruir();

	invencivel = true; //Fica invencível por alguns segundos quando toma dano
}

void Megaman::mover(float dt)
{
	sf::Vector2f posicao = getCoords();

	if (player1) //Player 1 usa as SETAS
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocidade -= velMax;
			direita = false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocidade += velMax;
			direita = true;
		}
		else
			velocidade = velocidade * 0.9;
	}

	else //Player 2 usa WASD
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocidade -= velMax; //aceleracao * dt;
			direita = false;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocidade += velMax; //aceleracao* dt;
			direita = true;
		}

		else
			velocidade = velocidade * 0.9;
	}

	if (velocidade > velMax) //Limita a velocidade
		velocidade = velMax;
	else if (velocidade < velMax * (-1))
		velocidade = velMax * (-1);

	cooldownNoChao += dt;
	if (cooldownNoChao > 0.1 && noChao) //Reseta a colisão com o chão de tempo em tempo para evitar o bug de levitação
	{
		noChao = false;
		cooldownNoChao = 0;
	}

	if (noChao)
	{
		velVertical = 0;
		
		if (player1) //Se for Player 1 usa seta para cima, se não, usa W
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
					velVertical = -350;
					noChao = false;
					std::cout << "Tenho " << getNumVidas() << " de HP" << std::endl;
					std::cout << "Tenho " << pontos << " pontos" << std::endl;
					std::cout << "FPS: " << 1.0 / dt << std::endl;
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				velVertical = -350.f;
				noChao = false;
			}
		}
	}
	
	//else
	//{
	//	velVertical += gravidade * dt;
	//}

	//if (posicao.x + velocidade * dt > 0.f)
	if(posicao.x + velocidade * dt >0)posicao.x += velocidade * dt;
	posicao.y += velVertical * dt;

	setCoords(posicao);
}

void Megaman::atirar(float dt)
{
	cooldownTiro += dt;
	
	if (player1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!teclaApertada && cooldownTiro >= 0.25)
			{
				sf::Vector2f pos = getCoords();

				ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
				LE->incluirEntidade(tiro);
				tiro->associaListaEntidades(LE);
				tiro->setGerenciadorGrafico(pGG);
				GC->incluirProjetil(tiro);

				cooldownTiro = 0;
				teclaApertada = true;
			}
		}
		else
		{
			teclaApertada = false;
		}
	}

	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			if (!teclaApertada && cooldownTiro >= 0.25)
			{
				sf::Vector2f pos = getCoords();

				ProjetilMegaman* tiro = new ProjetilMegaman(pos, direita);
				LE->incluirEntidade(tiro);
				tiro->associaListaEntidades(LE);
				tiro->setGerenciadorGrafico(pGG);
				GC->incluirProjetil(tiro);

				cooldownTiro = 0;
				teclaApertada = true;
			}
		}
		else
		{
			teclaApertada = false;
		}
	}
}

void Megaman::executar(float dt)
{
	mover(dt);
	atirar(dt);

	if(!noChao)
		sofrerAcaoDaGravidade(dt);

	if (invencivel)
	{
		framesInvencibilidade += dt;

		if (framesInvencibilidade >= 2)
		{
			framesInvencibilidade = 0;
			invencivel = false;
		}
	}
}

std::string Megaman::getTextureFile() 
{
	if (player1)
	{
		if (!invencivel)
		{
			if (direita)
				return "Sprites/Megaman/Parado/Parado1-dir.png";
			
			return "Sprites/Megaman/Parado/Parado1-esq.png";
		}
		else
		{
			if(direita)
				return "Sprites/Megaman/Parado/Parado1-Inv-dir.png";
			return "Sprites/Megaman/Parado/Parado1-Inv-esq.png";
		}
	}
	else
	{
		if (!invencivel)
		{
			if (direita)
				return "Sprites/Megaman/Parado/ParadoNH-dir.png";

			return "Sprites/Megaman/Parado/ParadoNH-esq.png";
		}
		else
		{
			if (direita)
				return "Sprites/Megaman/Parado/ParadoNH-Inv-dir.png";
			return "Sprites/Megaman/Parado/ParadoNH-Inv-esq.png";
		}
	}
}

void Megaman::salvar()
{
	int lugar = getId();
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()]["player1"] = player1;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["invencivel"] = invencivel;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["pontos"] = pontos;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size()-1]["teclaApertada"] = teclaApertada;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["cooldownTiro"] = cooldownTiro;
	dadosSalvos["id"][lugar][dadosSalvos["id"][lugar].size() - 1]["framesInvencibilidade"] = framesInvencibilidade;
	
	Personagem::salvar();
}
