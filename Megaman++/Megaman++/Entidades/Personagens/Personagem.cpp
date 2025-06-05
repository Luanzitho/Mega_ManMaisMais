#include "Personagem.h"

Personagem::Personagem(): num_vidas(0), velocidade(0), velVertical(0), aceleracao(0), gravidade(0), velMax(0)
{
}

Personagem::Personagem(int v):num_vidas(v)
{
}

Personagem::~Personagem()
{
}