#pragma once
#include "stdconfigs.h"

class Pessoas
{
	int idpessoa;
	int origem, destino;
	string nome;
public:
	Pessoas(int, int, int, string);
	~Pessoas();
	void DestruirPessoa();
	void Mostrar();
	void SetNome(string);
	void SetOrigem(int);
	void SetDestino(int);
	string GetNome();
	int GetOrigem();
	int GetDestino();
	int GetIDPessoa();
};

