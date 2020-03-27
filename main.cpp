#include "stdconfigs.h"
#include"Fronteiras.h"
#include"Pessoas.h"
#include"Grafo.h"


void main()
{
	while (1) {
		Grafo g(1);
		g.Load("grafo_1.txt", "pessoas.txt");

		/*Contagem de nos*/
		cout << "Numero de nos: " << g.ContarNos() << endl;

		/*Contagem de arcos*/
		cout << "Numero de arcos: " << g.ContarArcos() << endl;

		/*Função que devolve uma lista com o/s no/s com mais arcos*/
		list <int> *nomaisarcos;
		nomaisarcos = g.NoMaisArcos();
		cout << "\nNo/s com mais arcos: " << endl;
		for (auto i = nomaisarcos->begin(); i != nomaisarcos->end(); i++)
			cout << (*i) << " ";
		nomaisarcos->clear();
		delete nomaisarcos;

		/*Verifica existencia de adjacência*/
		if (g.Adjacencia(2, 1))
			cout << "\nExiste adjacencia" << endl;
		else
			cout << "\nNao existe adjacencia" << endl;

		/*Caminho qualquer entre dois vertices*/
		double  custo;
		list <int> *teste;
		teste = g.Caminho(2, 6, custo);
		cout << "\nCaminho possivel: " << endl;
		for (auto i = (*teste).begin(); i != (*teste).end(); i++)
			cout << (*i) << " ";
		teste->clear();
		delete teste;

		/*Lista com os vertices isolados*/
		list <int> *verticesisolados;
		verticesisolados = g.VerticesIsolados();
		cout << "\nVertices isolados:" << endl;
		for (auto i = verticesisolados->begin(); i != verticesisolados->end(); i++)
		{
			cout << (*i) << " ";
		}
		verticesisolados->clear();
		delete verticesisolados;

		/*Procura fronteira*/
		if (g.Search(26))
			cout << "\nFronteira Existe!" << endl;
		else
			cout << "\nNao existe fronteira" << endl;

		/*Remove vertice*/
		if (g.RemoverVertice(26))
		{
			cout << "Vertice removido com sucesso" << endl;
		}
		else
			cout << "Erro ao remover vertice" << endl;

		/*Remove aresta*/
		if (g.RemoverAresta(2, 1))
		{
			cout << "Aresta removida com sucesso" << endl;
		}
		else
			cout << "Erro ao remover aresta" << endl;

		/*Lista com os vertices de um determinado tipo*/
		list <int> *i = g.DevolveVerticesTipo("3");
		cout << "Fronteiras do tipo 3:" << endl;
		for (auto x = (*i).begin(); x != (*i).end(); x++)
			cout << *x << endl;
		i->clear();
		delete i;

		/*Caminho maximo entre 2 vertices*/
		double custototal2;
		list <int> *teste3;
		teste3 = g.CaminhoMaximo(2, 7, custototal2);
		cout << "\nO maior caminho: ";
		for (auto i = teste3->begin(); i != teste3->end(); i++)
			cout << *i << " ";
		teste3->clear();
		delete teste3;

		/*Caminho minimo entre dois vertices*/
		double custototal1;
		list <int> *teste2;
		teste2 = g.CaminhoMinimo(2, 7, custototal1);
		cout << "\nO menor caminho: ";
		for (auto i = teste2->begin(); i != teste2->end(); i++)
		{
			cout << (*i) << " ";
		}
		cout << "\n";
		teste2->clear();
		delete teste2;

		/*Verificar se existe ou nao caminho entre dois vertices*/
		if (g.PossivelCaminho(14, 3, 2))// existe caminho
			cout << "Existe caminho" << endl;
		if (g.PossivelCaminho(2, 6, 3))// Nao existe caminho
			cout << "Existe caminho" << endl;

		/*Lista com as fronteiras menos visitadas*/
		list<int> *menosvisistadas = new list <int>;
		g.FronteirasMenosVisitadas(*menosvisistadas);
		cout << "\nFronteiras menos visitadas: " << endl;
		for (auto p = (*menosvisistadas).begin(); p != (*menosvisistadas).end(); p++)
		{
			cout << *p << endl;
		}
		menosvisistadas->clear();
		delete menosvisistadas;

		/*Lista com os sitios inacessiveis*/
		list<int> *sitiosinacessiveis = new list <int>;
		g.SitiosInacessiveisAPartirDe(2, *sitiosinacessiveis);
		cout << "\nFronteiras inacessiveis :" << endl;
		for (auto i = (*sitiosinacessiveis).begin(); i != (*sitiosinacessiveis).end(); i++)
			cout << *i << endl;
		sitiosinacessiveis->clear();
		delete sitiosinacessiveis;

		/*Escreve em XML*/
		g.EscreverXML("teste.xml");

		/*Memoria */
		cout << "Memoria utilizada: " << g.Memoria() << " bytes" << endl;

		/*Ler XML*/
		g.LerXML("teste.xml");
	}
		system("pause");
}