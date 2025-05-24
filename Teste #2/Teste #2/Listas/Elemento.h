#pragma once
template <class TE> class Elemento
{
private:
	Elemento<TE>* pProx;
	TE* pInfo;

public:
	Elemento() { pProx = nullptr; pInfo = nullptr; }
	~Elemento() {}
	void incluir(TE* p) { if(p) pInfo = p; }
	void setProx(Elemento<TE>* pE) { if (pE) pProx = pE; }
	const Elemento<TE>* getProximo() { return pProx; }
	const TE* getpInfo() { return pInfo; } //Não consta no diagrama UML
};

