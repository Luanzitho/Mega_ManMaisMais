#pragma once
template <class TL> class Lista //Referencias: Dev Felipe e Burda
{
public:
	template <class TE> class Elemento
	{
	private:
		Elemento<TE>* pProx;
		TE* pInfo;

	public:
		Elemento() { pProx = nullptr; pInfo = nullptr; }

		~Elemento() {}

		void incluir(TE* p) { if (p) pInfo = p; }

		void setProx(Elemento<TE>* pE) { if (pE) pProx = pE; }

		Elemento<TE>* getProximo() { return pProx; }

		TE* getInfo() { return pInfo; }
	};

private:
	Elemento<TL>* pPrimeiro;
	Elemento<TL>* pUltimo;
	int tamanho;

public:
	Lista() { pPrimeiro = nullptr; pUltimo = nullptr; tamanho = 0; }
	
	~Lista(){}

	void incluir(TL* p)
	{
		if (p)
		{
			Elemento<TL>* temp = new Elemento<TL>;
			temp->incluir(p);

			if (!pPrimeiro)
			{
				pPrimeiro = temp;
				pUltimo = pPrimeiro;
			}
			else
			{
				pUltimo->setProx(temp);
				pUltimo = temp;
			}

			tamanho++;
		}
	}

	void remover(TL* p)
	{
		if (!p) return;
		
		Elemento<TL>* temp = pPrimeiro;
		Elemento<TL>* anteTemp = nullptr;
			
		while (temp->getInfo() != p) //Percorre a lista até achar o Elemento a remover
		{
			anteTemp = temp;
			temp = temp->getProximo();
		}
			
		if (temp == pPrimeiro) //Remove a primeira
		{
			pPrimeiro = temp->getProximo();
		}

		else if (temp == pUltimo) //Remove a última
		{				
			anteTemp->setProx(nullptr);
			pUltimo = anteTemp;
		}

		else //Remove uma no meio			
		{
			anteTemp->setProx(temp->getProximo());
		}

		delete temp;
		tamanho--;
		
	}

	void limpar()
	{
		Elemento<TL>* aux = pPrimeiro;

		while (aux)
		{
			Elemento<TL>* auxProx = aux->getProximo();

			if (aux->getInfo())
				delete aux->getInfo();  // deleta a entidade apontada

			delete aux;  // deleta o elemento da lista

			aux = auxProx;
		}

		pPrimeiro = nullptr;
		pUltimo = nullptr;
		tamanho = 0;
	}

	int getTamanho() { return tamanho; }

	Elemento<TL>* getpPrimeiro() { return pPrimeiro; }

	Elemento<TL>* getpUltimo() { return pUltimo; }
};