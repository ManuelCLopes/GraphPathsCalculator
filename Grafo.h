#include "stdconfigs.h"
#include"Fronteiras.h"
#include"Pessoas.h"
class Grafo
{
	int narcos;
	int ngrafo;
    list <Pessoas *> Lpessoas;                    /*Lista das pessoas */
	list <Fronteiras *> Lfronteiras;              /*Lista das fronteiras*/
	
	bool LerGrafo_txt(const string &);
	bool LerPessoas_txt(const string &);
	void mostrarLpessoas();
	void AddPessoas(int, int, int, string);
	bool CaminhoQualquer(int, int, int *, int *, int &, double &, list <int>*, int &);
	void AdicionarFronteira(Fronteiras*);
	void ProcuraMenorCaminho(list <int> *, int, int, int*, int *, int &, double &, int &, int &, int &, int &);
	void ProcuraMaiorCaminho(list <int> *, int, int, int*, int *, int &, double &, int &, int &, int &);
	bool ExisteCaminho(int, int, int[], int *, int &, int);
	bool AdicionarAresta(int, int, int);
	void GravarVisitas(list <int>*);
	bool AdicionarArestaXML(int, int, int);

public:
	void Destruir();
	bool LerXML(const string &);
	int Memoria();
	int nfronteiras;
	Grafo(int);
	~Grafo();
	bool Load(const string &, const string &);
	int ContarNos();
	int ContarArcos();
	list<int> *NoMaisArcos();
	bool Adjacencia(int, int);
	list<int> *VerticesIsolados();
	bool Search(int);
	bool RemoverAresta(int, int);
	bool RemoverVertice(int);
	void FronteirasMenosVisitadas(list<int> &);
	list<int> *DevolveVerticesTipo(const string &);
	list<int>* CaminhoMinimo(int, int, double &);
	list<int>* Caminho(int, int, double &);
	list<int> *CaminhoMaximo(int, int, double &);
	bool PossivelCaminho(int, int, int);
	void SitiosInacessiveisAPartirDe(int V1, list<int> &);
	void EscreverXML(const string &);

	void mostrarfronteiras();
	void MostrarArcos();
};

