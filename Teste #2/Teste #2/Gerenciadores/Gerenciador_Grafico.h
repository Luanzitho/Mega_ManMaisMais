#pragma once
#include "../Ente.h"
//#include "BiblioGrafica.h"

class Gerenciador_Grafico
{
private:
	//BiblioGrafica obj; D� a entender que tem um classe BiblioGrafica, mas n�o consta no diagrama UML...
	//(...)

public:
	Gerenciador_Grafico();
	~Gerenciador_Grafico();
	void desenharEnte(Ente* pE);
	//(...)
};