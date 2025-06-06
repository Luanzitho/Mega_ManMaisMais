#include "BigEye.h"

BigEye::BigEye()
{
}

BigEye::~BigEye()
{
}

void BigEye::mover(float dt)
{
}

void BigEye::executar(float dt)
{
	mover(dt);
}

void BigEye::danificar(Megaman* p)
{
	p->operator--();
}

std::string BigEye::getTextureFile()
{
	return "Sprites/Inimigos/BigEye1-blue.png";
}