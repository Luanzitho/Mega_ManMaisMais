#pragma once
#include "Elemento.h"

template <class TL> class Lista
{
private:
	Elemento<TL>* pPrimeiro;
	Elemento<TL>* pUltimo;
	int tam; //Não consta no diagrama UML

public:
	Lista() { pPrimeiro = nullptr; pUltimo = nullptr; tam = 0; }
	
	~Lista(){}
	
	void incluir(TL* p)
	{
		if (p) { //Testando se não é um ponteiro vazio
			if (pPrimeiro == nullptr) {
				pPrimeiro->incluir(p);
				pUltimo->incluir(p);
			}
			else {
				pUltimo->setProx(pUltimo);
				pUltimo->incluir(p);
			}
			tam++; //Aumentando o tamanho da lista
		}
	}

	void limpar(){} //Esvaziar a lista...?
	//(...)
	int getTam() { return tam; }

	//Talvez uma função que retorne o pPrimeiro para a função percorrer de ListaEntidades.h?
};
