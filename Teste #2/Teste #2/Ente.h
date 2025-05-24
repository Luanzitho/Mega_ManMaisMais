#pragma once
//#include "Gerenciador_Grafico.h"

//class Gerenciador_Grafico;

class Ente
{
protected:
	int id;
	//static Gerenciador_Grafico* pGG;
	//Figura* pFig; Dá a entender que tem uma classe Figura, mas não consta no diagrama UML...
	//(...)

public:
	Ente();
	~Ente();
	virtual void executar()=0; //Função virtual pura
	void desenhar();
};

