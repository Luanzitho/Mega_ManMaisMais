#pragma once
#include "../Ente.h"
//#include "BiblioGrafica.h"

class Gerenciador_Grafico
{
private:
	//BiblioGrafica obj; Dá a entender que tem um classe BiblioGrafica, mas não consta no diagrama UML...
	//(...)

public:
	Gerenciador_Grafico();
	~Gerenciador_Grafico();
	void desenharEnte(Ente* pE);
	//(...)
};