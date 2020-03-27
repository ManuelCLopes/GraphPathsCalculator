#pragma once
#include "stdconfigs.h"

class Fronteiras
{
	int nfronteira;
	int nvisitas;
public:
	map<int, int> Ladj; // nfronteira adjacente e distancia
	Fronteiras(int);
	~Fronteiras();
	void DestruirFronteira();
	int GetAdj();
	int GetnFronteira();
	int Getnvisitas();
	void IncVisitas();
	void DecVisitas();
	virtual int GetTipo() { return 0; }
	virtual double GetPreco() { return 0; }
	virtual int GetKilos() { return 0; }
	bool InserirArco(int, int);
};

class Fronteira_Oficial :
	public Fronteiras
{
public:
	Fronteira_Oficial(int);
	~Fronteira_Oficial();
	int GetTipo() { return 3; }
	double GetPreco() { return 0; }  

};

class Fronteira_tipo1 :
	public Fronteiras
{
	int pagamento = 10;
public:
	Fronteira_tipo1(int);
	~Fronteira_tipo1();
	int GetTipo() { return 1; }
	double GetPreco() { return 10; }  //10€
};

class Fronteira_tipo2 :
	public Fronteiras
{
	int pagamento = 5;
	int mercadoria = 1;
public:
	Fronteira_tipo2(int);
	~Fronteira_tipo2();
	int GetTipo() { return 2; }
	double GetPreco() { return 5; } //5 €
	int GetKilos() { return 1; }  //1Kg
};

