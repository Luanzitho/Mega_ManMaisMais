#pragma once
//#include "Gerenciador_Grafico.h"

//class Gerenciador_Grafico;

class Ente
{
protected:
	int id;
	//static Gerenciador_Grafico* pGG;
	//Figura* pFig; D� a entender que tem uma classe Figura, mas n�o consta no diagrama UML...
	//(...)

public:
	Ente();
	~Ente();
	virtual void executar()=0; //Fun��o virtual pura
	void desenhar();
};

