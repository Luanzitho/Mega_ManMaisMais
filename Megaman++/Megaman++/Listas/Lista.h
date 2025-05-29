#pragma once
template <class TL> class Lista //Referencias: Dev Felipe e Burda
{
private:
	Elemento<TL>* pPrimeiro;
	Elemento<TL>* pUltimo;

	template <class TE> Elemento
	{
	private:
		Elemento<TE>*pProx;
		TE* pInfo;

	public:
		Elemento() { pProx = nullptr; pInfo = nullptr; }

		~Elemento() {}

		void incluir(TE* p) { if (p) pInfo = p; }

		void setProx(Elemento<TE>* pE) { if (pE) pProx = p; }

		Elemento<TE>* getProximo() { return pProx; }
	}

public:
	Lista() { pPrimeiro = nullptr; pUltimo = nullptr; }
	
	~Lista(){}

	void incluir(TL* p)
	{
		if (!pPrimeiro)
		{
			pPrimeiro = p;
			pUltimo = p;
		}
		else
		{
			pUltimo
		}
	}

	void limpar()
	{
	
	}
};

