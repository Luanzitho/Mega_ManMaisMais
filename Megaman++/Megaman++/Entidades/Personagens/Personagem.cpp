#include "Personagem.h"

Personagem::Personagem():num_vidas(0)
{
}

Personagem::Personagem(int v):num_vidas(v)
{
}

Personagem::~Personagem()
{
}

void Personagem::mover()
{
	x=x+0.1;
}

void Personagem::executar()
{
	mover();
}

std::string Personagem::getTextureFile()
{
	return "Sprites/Megaman/Parado/Parado1.png";
}