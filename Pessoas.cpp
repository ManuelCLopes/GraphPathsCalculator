#include "Pessoas.h"

Pessoas::Pessoas(int id, int ori, int dest, string n)
{
	idpessoa = id;
	nome = n;
	origem = ori;
	destino = dest;
}


Pessoas::~Pessoas()
{
}
void Pessoas::DestruirPessoa()
{
	nome.clear();
}
void Pessoas::Mostrar()
{
	cout << "Nome: " << nome << "\tOrigem: " << origem << "\tDestino: " << destino << endl;
}
void Pessoas::SetNome(string n) {
	nome = n;
}
void Pessoas::SetOrigem(int o) {
	origem = o;
}
void Pessoas::SetDestino(int d) {
	destino = d;
}
string Pessoas::GetNome() {
	return nome;
}
int Pessoas::GetOrigem() {
	return origem;
}
int Pessoas::GetDestino() {
	return destino;
}
int Pessoas::GetIDPessoa()
{
	return idpessoa;
}