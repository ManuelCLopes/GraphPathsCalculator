#include "Fronteiras.h"



Fronteiras::Fronteiras(int n)
{
	nfronteira = n;
	nvisitas = 0;
}


Fronteiras::~Fronteiras()
{
}
void Fronteiras::DestruirFronteira()
{
	Ladj.clear();
}
bool Fronteiras::InserirArco(int v, int dist)
{
	size_t tam = Ladj.size(); // size_t em vez de int para nao perder dados
	Ladj.insert(pair<int, int>(v, dist));
	if (Ladj.size() > tam)
	{
		return true;
	}
	return false;
}

int Fronteiras::GetnFronteira()
{
	return nfronteira;
}
int Fronteiras::Getnvisitas()
{
	return nvisitas;
}

Fronteira_Oficial::Fronteira_Oficial(int id)
	:Fronteiras(id)
{
}
int Fronteiras::GetAdj()
{
	return Ladj.size();
}
void Fronteiras::IncVisitas()
{
	nvisitas++;
}
void Fronteiras::DecVisitas()
{
	nvisitas--;
}

Fronteira_Oficial::~Fronteira_Oficial()
{
}


Fronteira_tipo1::Fronteira_tipo1(int id)
	:Fronteiras(id)
{
}


Fronteira_tipo1::~Fronteira_tipo1()
{
}

Fronteira_tipo2::Fronteira_tipo2(int id)
	:Fronteiras(id)
{
}


Fronteira_tipo2::~Fronteira_tipo2()
{
}

