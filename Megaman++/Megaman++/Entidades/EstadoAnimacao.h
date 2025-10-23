#pragma once

class EstadoAnimacao
{
public:
	bool Parado;
	bool Andando;
	bool Pulando;
	bool Atacando;
	bool Machucado;
	bool Morrendo;

	int alturaSprite;
	int larguraSprite;
	int numFrames;
	int frameAtual;
};