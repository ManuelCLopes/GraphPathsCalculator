#include "Grafo.h"

Grafo::Grafo(int n)
{
	ngrafo = n;
}
Grafo::~Grafo()
{
	Destruir();
}
int Grafo::Memoria()
{
	int total = 0;
	total += sizeof(narcos);
	total += sizeof(ngrafo);
	total += sizeof(nfronteiras);
	total += sizeof(Lpessoas);
	for (auto i = Lpessoas.begin(); i != Lpessoas.end(); i++)
	{
		total += sizeof((*i)->GetDestino());
		total += (*i)->GetNome().length() *sizeof(char) + sizeof((*i)->GetNome());
		total += sizeof((*i)->GetOrigem());
		total += sizeof((*i)->GetIDPessoa());
	}
	total += sizeof(Lfronteiras);
	for (auto j = Lfronteiras.begin(); j != Lfronteiras.end(); j++)
	{
		total += sizeof((*j)->GetnFronteira());
		total += sizeof((*j)->Getnvisitas());
		total += sizeof((*j)->GetPreco());
		total += sizeof((*j)->GetTipo());
		total += sizeof((*j)->GetKilos());
		total += sizeof((*j)->Ladj);
		for (map <int, int> ::iterator k = (*j)->Ladj.begin(); k != (*j)->Ladj.end(); k++)
		{
			total += sizeof(k->first);
			total += sizeof(k->second);
		}
	}
	return total;
}
void Grafo::Destruir()
{
	//Esvazia string do nome em cada pessoa, de seguida destrói ponteiro. Depois limpa-se a lista de pessoas
	for (auto p = Lpessoas.begin(); p != Lpessoas.end(); p++) {
		(*p)->DestruirPessoa(); 
		delete (*p);
	}
	Lpessoas.clear();
	//Esvazia lista de adjacencias e destroi ponteiro.  Depois limpa-se a lista de fronteiras
	for (auto f = Lfronteiras.begin(); f != Lfronteiras.end(); f++) 
	{
		(*f)->DestruirFronteira();
		delete (*f);
	}
	Lfronteiras.clear(); 
}

bool Grafo::LerGrafo_txt(const string &fich_grafo)
{
	ifstream FICH_GRAFO, FICH_PESSOAS;
	string fronteira, tipo, cord, lixo, v1, v2, distancia, total_fronteiras, total_arcos; 

	// Abre um arquivo TEXTO para LEITURA
	FICH_GRAFO.open(fich_grafo);
	if (FICH_GRAFO.is_open())
	{
		while (!FICH_GRAFO.eof())
		{
			getline(FICH_GRAFO, total_fronteiras);
			getline(FICH_GRAFO, total_arcos);
			narcos = stoi(total_arcos);
			
			for(int i = 0 ; i < stoi(total_fronteiras); i++)
			{
				getline(FICH_GRAFO, fronteira, ';');
				getline(FICH_GRAFO, cord, ';');
				getline(FICH_GRAFO, cord, ';');
				getline(FICH_GRAFO, tipo);
				if (stoi(tipo) == 1) // Fronteira do tipo 1
					AdicionarFronteira(new Fronteira_tipo1(stoi(fronteira)));
				if (stoi(tipo) == 2) // Fronteira do tipo 2 
					AdicionarFronteira(new Fronteira_tipo2(stoi(fronteira)));
				if (stoi(tipo) == 3) // Fronteira Oficial
					AdicionarFronteira(new Fronteira_Oficial(stoi(fronteira)));
			}
			if (stoi(total_fronteiras) != nfronteiras) // Caso haja algum erro na gravação das fronteiras
			{
				cout << "Erro a ler fronteiras" << endl;
				return false;
			}
			getline(FICH_GRAFO, lixo);
			while (!FICH_GRAFO.eof())
			{
				getline(FICH_GRAFO, v1, ';');
				getline(FICH_GRAFO, v2, ';');
				getline(FICH_GRAFO, distancia);

				if (!AdicionarAresta(stoi(v1), stoi(v2), stoi(distancia)))
				{
					cout << "ERRO AO ADICIONAR ARESTA" << endl;
					return false;
				}
			}
			if (ContarArcos() != stoi(total_arcos))//Caso tenham sido carregados um diferente numero de arcos daquele dado no inicio do ficheiro
				narcos = ContarArcos();
				cout << "\nNumero de arcos inicialmente nao corresponde ao numero de arcos real!\nO programa ira carregar os dados mesmo assim.\n" << endl;
		}
		FICH_GRAFO.close();
	}
	else  // Se houve erro na abertura
		return false;
	return true;
}
bool Grafo::LerXML(const string &s)
{
	Destruir();
	ifstream file(s);
	string lixo, line, numero_grafo, nadj, numero_arcos, numero_fronteiras, numero_pessoas, IDPessoa, NomePessoa, vertice, distancia, NFronteira, NVisitas, Tipo, Adjacencia, Distancia, origem, destino;
	if (file.is_open())
	{
			//<xml version="1.0">
			getline(file, lixo);

			//<Grafo>
			getline(file, lixo);

			//Numero de grafo
			getline(file, lixo, '\''); getline(file, numero_grafo, '\''); getline(file, lixo);

			//Numero de arcos
			getline(file, lixo, '\''); getline(file, numero_arcos, '\''); getline(file, lixo);

			//numero de fronteiras
			getline(file, lixo, '\''); getline(file, numero_fronteiras, '\''); getline(file, lixo);

			for(int x = 0; x < stoi(numero_fronteiras); x++)
			{
				getline(file, lixo, '\'');
				getline(file, NFronteira, '\'');
				getline(file, lixo, '\'');
				getline(file, NVisitas, '\'');
				getline(file, lixo, '\'');
				getline(file, Tipo, '\'');
				getline(file, lixo);

				if (stoi(Tipo) == 1) // Fronteira do tipo 1
					AdicionarFronteira(new Fronteira_tipo1(stoi(NFronteira)));
				if (stoi(Tipo) == 2) // Fronteira do tipo 2 
					AdicionarFronteira(new Fronteira_tipo2(stoi(NFronteira)));
				if (stoi(Tipo) == 3) // Fronteira Oficial
					AdicionarFronteira(new Fronteira_Oficial(stoi(NFronteira)));

				//numero de adjacencias
				getline(file, lixo, '\''); getline(file, nadj, '\''); getline(file, lixo);

				if (stoi(nadj) > 0) 
				{
					for (int i = 0; i < stoi(nadj); i++)
					{
						getline(file, lixo, '\'');
						getline(file, vertice, '\'');
						getline(file, lixo, '\'');
						getline(file, distancia, '\'');
						getline(file, lixo);

						if (!AdicionarArestaXML(stoi(NFronteira), stoi(vertice), stoi(distancia)))
						{
							cout << "ERRO AO ADICIONAR ARESTA" << endl;
							return false;
						}
					}
				}
			}
			//Total de pessoas
			getline(file, lixo, '\''); getline(file, numero_pessoas, '\''); getline(file, lixo);

			for(int y = 0; y < stoi(numero_pessoas); y++)
			{
				getline(file, lixo, '\''); getline(file, IDPessoa, '\''); getline(file, lixo, '\''); getline(file, NomePessoa, '\''); getline(file, lixo, '\''); getline(file, origem, '\''); getline(file, lixo, '\''); getline(file, destino, '\''); getline(file, lixo);
				AddPessoas(stoi(IDPessoa), stoi(origem), stoi(destino), NomePessoa);
			}
		file.close();
	}
	else //Erro na abertura
		return false;
	return true;
}
bool Grafo::LerPessoas_txt(const string &fich)
{
	ifstream FICH_PESSOAS;
	string idPessoa, NomeP, f1, f2; // como apagar str da memoria ??
	
	// Abre um arquivo TEXTO para LEITURA
	FICH_PESSOAS.open(fich);
	if (FICH_PESSOAS.is_open())
	{
		while (!FICH_PESSOAS.eof())
		{
				getline(FICH_PESSOAS, idPessoa, ';');
				getline(FICH_PESSOAS, NomeP, ';');
				getline(FICH_PESSOAS, f1, ';');
				getline(FICH_PESSOAS, f2);	
				AddPessoas(stoi(idPessoa), stoi(f1), stoi(f2), NomeP);
		}
		FICH_PESSOAS.close();
	}
	else  // Se houve erro na abertura
		return false;
	return true;
}
bool Grafo::Load(const string &fich_grafo, const string &fich_pessoas)
{
	return (LerGrafo_txt(fich_grafo) && LerPessoas_txt(fich_pessoas)); //Caso a leitura de um dos ficheiros tenha dado return false, Load também dará
}
void Grafo::EscreverXML(const string &s)
{
	std::ofstream file;
	file.open(s);
	file << "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>" << endl;
	file << "<Grafo>" << endl;
		file << "\t<NumeroGrafo n='" << ngrafo << "'>" << "</NumeroGrafo>" << endl;
		file << "\t<NumeroArcos n='" << narcos << "'>" << "</NumeroArcos>" << endl;
		file << "\t<LFronteiras Numero_fronteiras='" << nfronteiras << "'>" << endl;
		for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++)
		{
			file << "\t\t<Fronteira nfronteira='" << (*i)->GetnFronteira() << "' nvisitas='" << (*i)->Getnvisitas() << "' tipo='" << (*i)->GetTipo() << "'>" << endl;
			file << "\t\t\t<Ladj Numero_adjacencias='" << (*i)->GetAdj() << "'>" << endl;
			for (auto j = (*i)->Ladj.begin(); j != (*i)->Ladj.end(); j++)
			{
				file << "\t\t\t\t<Adjacencia vertice='" << (*j).first << "' distancia='" << (*j).second << "'>" << "</Adjacencia>" << endl;
			}
			file << "\t\t\t</Ladj>" << endl;
			file << "\t\t</Fronteira>" << endl;
		}
		file << "\t</LFronteiras>" << endl;

		file << "\t<LPessoas Numero_pessoas='" << Lpessoas.size() << "'>" << endl;
			for (auto i = Lpessoas.begin(); i != Lpessoas.end(); i++)
			{
				file << "\t\t<Pessoa id='" << (*i)->GetIDPessoa() << "' nome='" << (*i)->GetNome() << "' origem='" << (*i)->GetOrigem() << "' destino='" << (*i)->GetDestino() << "'>" << "</Pessoa>" << endl;
			}
		file << "\t </LPessoas>" << endl;

	file << "</Grafo>" << endl;
}

void Grafo::mostrarLpessoas()
{
	for (auto i = Lpessoas.begin(); i != Lpessoas.end(); i++)
		(*i)->Mostrar();
}
void Grafo:: AddPessoas(int id, int o, int d, string n)
{
	Pessoas *p= new Pessoas(id, o, d, n);//Cria ponteiro para uma nova pessoa
	Lpessoas.push_back(p); //insere a pessoa no fim da lista das pessoas
}
int Grafo::ContarNos()
{
	return Lfronteiras.size();
}
int Grafo::ContarArcos()
{
	int x = 0;
	for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++)
		if ((*i)->GetAdj() != 0)
			for (auto p = (*i)->Ladj.begin(); p != (*i)->Ladj.end(); p++)
				x++;
	return x / 2;
}
list<int> *Grafo::NoMaisArcos()
{
	list <int> *nomaisarcos = new list<int>; 
	int max = 0;
	for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++)
	{
		if ((*i)->GetAdj() == max)//Se tiver o mesmo numero de arcos acrescenta à lista
			nomaisarcos->push_back((*i)->GetnFronteira());
		if ((*i)->GetAdj() > max)//Se tiver mais arcos limpa a lista, insere numero da fronteira e estabelece um novo maximo de arcos
		{
			max = (*i)->GetAdj();
			nomaisarcos->clear();
			nomaisarcos->push_back((*i)->GetnFronteira());
		}
	}
	return nomaisarcos;
}
void Grafo::AdicionarFronteira(Fronteiras* f)//Insere fronteira na lista de fronteiras e incremente o numero de fronteiras do grafo
{
	Lfronteiras.push_back(f);
	this->nfronteiras++;
}
bool Grafo::AdicionarAresta(int v1, int v2, int dist)
{
	int verificacao = 0; // utilização desta variavel de verificacao para aumentar a eficacia da função
	for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++)
	{
		if ((*i)->GetnFronteira() == v1)
		{
			if ((*i)->InserirArco(v2, dist))
			{
				verificacao++;
			}
		}
		if ((*i)->GetnFronteira() == v2)
		{
			if ((*i)->InserirArco(v1, dist))
			{
				verificacao++;
			}
		}
		if (verificacao == 2)
			return true;
	}
		return false;
}
bool Grafo::AdicionarArestaXML(int v1, int v2, int dist)
{//versao reduzida da função AdicionarAresta. Nesta função adiciona a fronteira2 e distancia na lista de adjacências da fronteira1
	int verificacao = 0;
	for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++)
		if ((*i)->GetnFronteira() == v1)
		{
			if ((*i)->InserirArco(v2, dist))
				verificacao++;
			break;
		}
	if (verificacao == 1)
		return true;
	return false;
}
bool Grafo::Adjacencia(int v1, int v2)
{
	for (auto x = Lfronteiras.begin(); x != Lfronteiras.end(); x++) 
	{
		if ((*x)->GetnFronteira() == v1)
		{
			if ((*x)->GetAdj() == 0)// se nao tiver adjacencias retorna sempre falso
				return false;
			else
			{
				auto p = (*x)->Ladj.find(v2);//procura vertice na sua lista de adjacencias
				if (p != (*x)->Ladj.end())
					return true;
				else
					return false;
			}
		}
		if ((*x)->GetnFronteira() == v2)
		{
			if ((*x)->GetAdj() == 0)
				return false;
			else
			{
				auto p = (*x)->Ladj.find(v1);
				if (p != (*x)->Ladj.end())
					return true;
				else
					return false;
			}
		}
	}
	return false;
}
list<int> *Grafo::VerticesIsolados()//vertices isolados = vertices sem adjacencias
{
	list <int> *verticesisolados = new list<int>;
	for (auto p = Lfronteiras.begin(); p != Lfronteiras.end(); p++)
	{
		if ((*p)->GetAdj() == 0)
			verticesisolados->push_back((*p)->GetnFronteira());
	}
	return verticesisolados;
}
bool Grafo::Search(int v)
{
	for (auto p = Lfronteiras.begin(); p != Lfronteiras.end(); p++)
	{
		if ((*p)->GetnFronteira() == v)
			return true;
	}
	return false;
}
bool Grafo::RemoverAresta(int v1, int v2)
{
	if (!Adjacencia(v1, v2)) //Se vertices nao forem adjacentes nao ha aresta para remover
		return false;

	int itf = 0;
	for (auto p = Lfronteiras.begin(); p != Lfronteiras.end(); p++) // apagar adjacencia nas listas de adjacencias dos dois vertices
	{
		if (v1 == (*p)->GetnFronteira())
		{
			(*p)->Ladj.erase(v2);
			itf++;
		}
		if (v2 == (*p)->GetnFronteira())
		{
			(*p)->Ladj.erase(v1);
			itf++;
		}
		if (itf == 2)
			return true;
	}
	return false;
}

bool Grafo::RemoverVertice(int v)
{
	if (!Search(v)) // Se o vertice nao existir ja nao se remove nada
		return false;

	bool sucesso = false;
	int adjacencias_retiradas = 0;//variavel de controlo de adjacencias eliminadas
	int total_adj;
	list <Fronteiras*>::iterator aux;
	for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++) // Apaga os dados do vertice v nas fronteiras com quem tem adjacencia
	{
		if ((*i)->GetnFronteira() == v)
		{
			aux = i;
			if ((*i)->GetAdj() != 0) // se o vertice nao tiver adjacencia ja nao é preciso percorrer restantes fronteiras para eliminar a fronteira desejada
				total_adj = (*i)->GetAdj();
			else
			{
				sucesso = true;
				break;
			}
			delete (*i);
			i++;
		}
		if ((*i)->GetnFronteira() != v)
		{
			if ((*i)->Ladj.find(v) != (*i)->Ladj.end()) {
				adjacencias_retiradas++;
				narcos--;
				(*i)->Ladj.erase(v);
			}
		}
		if (adjacencias_retiradas != total_adj) // verificação a ver se o numero de adjacencias eliminadas é igual ao numero de adjacencias inicial
			sucesso = false;
		else sucesso = true;
	}
	Lfronteiras.erase(aux);
	delete(*aux);
	this->nfronteiras--;
	return sucesso;
}
void Grafo::GravarVisitas(list <int>* l)
{
	for (list <int>::iterator i = l->begin(); i != l->end(); i++)
	{
		for (auto f = Lfronteiras.begin(); f != Lfronteiras.end(); f++)
		{
			if ((*f)->GetnFronteira() == (*i))
			{
				(*f)->IncVisitas();
				break;
			}
		}
	}
}
void Grafo::FronteirasMenosVisitadas(list<int> &Lv)
{
	int min = 30; // 30 é um numero hipotetico
	double custo;
	
	for (list <Pessoas*>::iterator p = Lpessoas.begin(); p != Lpessoas.end(); p++)// Obrigar pessoas a percorrer o seu caminho
	{	list <int> *aux;
		aux = Caminho((*p)->GetOrigem(), (*p)->GetDestino(), custo);
		aux->clear();
		delete aux;
	}
	list <Fronteiras*> ::iterator x;
	for (x = Lfronteiras.begin(); x != Lfronteiras.end(); x++)
	{
		if ((*x)->Getnvisitas() == min)
			Lv.push_back((*x)->GetnFronteira());
		if ((*x)->Getnvisitas() < min)
		{
			min = (*x)->Getnvisitas();
			Lv.clear();
			Lv.push_back((*x)->GetnFronteira());
		}
	}
	
}
list<int> *Grafo::DevolveVerticesTipo(const string &tipo)
{
	list <int> *devolververticestipo = new list<int>;

	for (auto x = Lfronteiras.begin(); x != Lfronteiras.end(); x++)
		if ((*x)->GetTipo() == stoi(tipo))
			devolververticestipo->push_back((*x)->GetnFronteira());
	return devolververticestipo;
}
list <int> * Grafo::Caminho(int v1, int v2, double &custo)
{
	list <int> *c = new list <int> ; 
	int * visit = new int[nfronteiras + 1];
	for (int i = 1; i <= nfronteiras; i++)
		visit[i] = 0;

	int * path = new int[nfronteiras];
	int npassagens = 0;
	double preco = 0;//custo da viagem
	int mercadoria = 0;//peso da mercadoria transportada
	CaminhoQualquer(v1, v2, visit, path, npassagens, preco, c, mercadoria);
	GravarVisitas(c);
	custo = preco;
	
	delete [] path;
	delete [] visit;
	return c;
}

bool Grafo::CaminhoQualquer(int pos, int d, int visited[], int * path, int &path_index, double &custo, list <int> *aux, int &peso)
{
	//Marca vertice como visitado, acrescenta vertice ao caminho e incrementa numero de fronteiras do caminho 
	visited[pos] = 1;
	path[path_index] = pos;
	path_index++;
	
	if (pos == d)//se encontra o destino insere todas as fronteiras do caminho na lista aux e sai da função
	{
		for (int i = 0; i < path_index; i++)
		{
			aux->push_back(path[i]);
		}
		return true;
	}
	else ///Se o vertice nao for o destino
	{
		visited[d] = 0;//forçar o programa a entender que o destino ainda nao foi visitado  
		
		for (auto it = Lfronteiras.begin(); it != Lfronteiras.end(); it++)
		{
			if ((*it)->GetnFronteira() == pos)
			{
				for (auto a = (*it)->Ladj.begin(); a != (*it)->Ladj.end(); ++a)//percorre todos os vertices adjacentes a fronteira 
					if (!visited[a->first]) {
						custo += (*it)->GetPreco();
						peso += (*it)->GetKilos();
						if(peso <= MAXMERCADORIA)
							if (CaminhoQualquer(a->first, d, visited, path, path_index, custo, aux, peso))
								return true;// caso tenha encontrado o destino a função vai retornar true 
						custo -= (*it)->GetPreco();
						peso -= (*it)->GetKilos();
					}
				break;
			}
		}
	}//Remove vertice do caminho atual e decrementa o numero de fronteiras do caminho
	path_index--;
	visited[pos] = 0;
	return false;
}
void Grafo::ProcuraMenorCaminho(list <int> *menor_caminho, int pos, int d, int visited[], int * path, int &path_index, double &preco, int &distancia, int &menor_dist, int &menor_custo, int &peso)
{
	visited[pos] = 1;
	path[path_index] = pos;
	path_index++;

	if (pos == d) //se encontra o destino
	{
		if (distancia < menor_dist || (distancia == menor_dist && preco < menor_custo))// se o caminho for menor OU (se o caminho for igual e tiver um custo menor)
		{
			menor_caminho->clear();
			for (auto it = Lfronteiras.begin(); it != Lfronteiras.end(); ++it)
			{
				if ((*it)->GetnFronteira() == d)
				{
					preco = preco + (*it)->GetPreco();
				}
			}
			for (int i = 0; i < path_index; i++)
			{
				menor_caminho->push_back(path[i]);
			}
			menor_dist = distancia;
		}
	}
	else //  o vertice nao for o destino
	{
		visited[d] = 0;
		// Recur for all the vertices adjacent to current vertex 
		for (auto it = Lfronteiras.begin(); it != Lfronteiras.end(); it++)
		{
			if ((*it)->GetnFronteira() == pos)
			{
				for (auto a = (*it)->Ladj.begin(); a != (*it)->Ladj.end(); ++a)
				{
					if (!visited[a->first])
					{
						preco += (*it)->GetPreco();
						distancia += a->second;
						peso += (*it)->GetKilos();
						if(peso <= MAXMERCADORIA) // Caso o peso que a pessoa leve não ultrapasse o peso máximo mercadoria
							ProcuraMenorCaminho(menor_caminho, a->first, d, visited, path, path_index, preco, distancia, menor_dist, menor_custo, peso);
						preco -= (*it)->GetPreco();
						distancia -= a->second;
						peso -= (*it)->GetKilos();
					}
				}
				break;
			}
		}
	}
	path_index--;
	visited[pos] = 0;
}
void Grafo::ProcuraMaiorCaminho(list <int> *maior_caminho, int pos, int d, int visited[], int * path, int &path_index, double &preco, int &distancia, int &maior_dist, int &peso)
{
	visited[pos] = 1;
	path[path_index] = pos;
	path_index++;

	if (pos == d) //Se encontra o destino
	{
		if (distancia > maior_dist)// se o caminho for menor OU (se o caminho for igual e tiver um custo menor
		{
			maior_caminho->clear();

			for (auto it = Lfronteiras.begin(); it != Lfronteiras.end(); ++it)
			{
				if ((*it)->GetnFronteira() == d)
				{
					preco = preco + (*it)->GetPreco();
				}
			}
			for (int i = 0; i < path_index; i++)
			{
				maior_caminho->push_back(path[i]);
			}
			maior_dist = distancia;//atualiza maior distancia
		}
	}
	else // o vertice nao for o destino
	{
		visited[d] = 0;
		for (auto it = Lfronteiras.begin(); it != Lfronteiras.end(); it++)
		{
			if ((*it)->GetnFronteira() == pos)
			{
				for (auto a = (*it)->Ladj.begin(); a != (*it)->Ladj.end(); ++a)
				{
					if (!visited[a->first])
					{
						preco += (*it)->GetPreco();
						distancia += a->second;
						peso += (*it)->GetKilos();
						if(peso <= MAXMERCADORIA)
							ProcuraMaiorCaminho(maior_caminho, a->first, d, visited, path, path_index, preco, distancia, maior_dist, peso);
						preco -= (*it)->GetPreco();
						distancia -= a->second;
						peso -= (*it)->GetKilos();
					}
				}
				break;
			}
		}
	}
	path_index--;
	visited[pos] = 0;
}
list <int>* Grafo::CaminhoMinimo(int v1, int v2, double &custo_total)
{
	list <int> *caminho_minimo = new list <int>;
	int menor_distancia = 10000;
	int menor_custo = 100000;
	int * visita = new int[nfronteiras + 1];
	for (int i = 1; i <= nfronteiras; i++)
		visita[i] = 0;
	int * pathh = new int[nfronteiras];
	int npassagens = 0;
	double preco = 0;
	int mercadoria = 0;
	int distancia = 0;

	ProcuraMenorCaminho(caminho_minimo, v1, v2, visita, pathh, npassagens, preco, distancia, menor_distancia, menor_custo, mercadoria);

	custo_total = preco;
	delete [] visita;
	delete [] pathh;
	return caminho_minimo;
}
list<int> *Grafo::CaminhoMaximo(int v1, int v2, double &custo_total)
{
	list <int> *caminho_maximo = new list <int>;
	int maior_distancia = 0;
	int * visita = new int[nfronteiras + 1];
	for (int i = 1; i <= nfronteiras; i++)
		visita[i] = 0;
	int * pathh = new int[nfronteiras];
	int npassagens = 0;
	double preco = 0;
	int distancia = 0;
	int mercadoria = 0;

	ProcuraMaiorCaminho(caminho_maximo, v1, v2, visita, pathh, npassagens, preco, distancia, maior_distancia, mercadoria);

	custo_total = preco;
	delete [] visita;
	delete [] pathh;
	return caminho_maximo;
}
bool Grafo::PossivelCaminho(int v1, int v2, int TipoFronteira)
{
	int * visit = new int[nfronteiras + 1];
	for (int i = 1; i <= nfronteiras; i++)
		visit[i] = 0;
	int * path = new int[nfronteiras];
	int npassagens = 0;
	bool retorno = ExisteCaminho(v1, v2, visit, path, npassagens, TipoFronteira); //Criação da variavel bool para sre possivel a libertação de memoria de visit e path

	delete [] visit;
	delete [] path;
	return retorno;
}
bool Grafo::ExisteCaminho(int pos, int d, int visited[], int * path, int &path_index, int tipof)
{
	visited[pos] = 1;
	path[path_index] = pos;
	path_index++;
	//se chegar ao destino retorno  verdadeiro
	if (pos == d) {
		return true;
	}
	else 
	{
		visited[d] = 0;
		for (auto it = Lfronteiras.begin(); it != Lfronteiras.end(); it++)
			if ((*it)->GetnFronteira() == pos)
			{
				for (auto a = (*it)->Ladj.begin(); a != (*it)->Ladj.end(); a++)
					if (!visited[a->first] && ((*it)->GetTipo() == tipof))
						if (ExisteCaminho(a->first, d, visited, path, path_index, tipof))
							return true;
				break;
			}
	}
	path_index--;
	visited[pos] = 0;
	return false;
}

void Grafo::SitiosInacessiveisAPartirDe(int V1, list<int> &Lv)
{
	for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++)
	{
		if ((*i)->GetnFronteira() == V1 && (*i)->GetAdj() == 0) //Se for isolado
		{
			for (auto v = Lfronteiras.begin(); v != Lfronteiras.end(); v++)
				if ((*v)->GetnFronteira() != V1)
					Lv.push_back((*v)->GetnFronteira());
			break;
		}

		else
			if ((*i)->GetnFronteira() != V1)
				if ((*i)->GetAdj() == 0) // Se o vertice em questao for isolado
					Lv.push_back((*i)->GetnFronteira());
	}
}
void Grafo::MostrarArcos()
{//Função apenas para mostrar os arcos do grafo
	for (auto a = Lfronteiras.begin(); a != Lfronteiras.end(); a++)
	{
		for (auto x = (*a)->Ladj.begin(); x != (*a)->Ladj.end(); x++)
			cout << "v1: " << (*a)->GetnFronteira() << "\tv2: " << (*x).first << endl;
	}
}
void Grafo::mostrarfronteiras()
{
	for (auto i = Lfronteiras.begin(); i != Lfronteiras.end(); i++)
		cout << (*i)->GetnFronteira() << endl;
}