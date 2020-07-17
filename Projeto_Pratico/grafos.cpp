#include "pch.h"
#include "grafos.h"

using namespace std;
grafos::grafos()
{
	
	cout << "Passei em " << __FUNCTION__ << endl;
}
grafos::~grafos()
{
	

	for (list<fronteira *>::iterator iter = LF.begin();
		iter != LF.end(); ++iter)
	{
		delete *iter;
	}
	for (list<aresta *>::iterator iter = LAresta.begin();
		iter != LAresta.end(); ++iter)
	{
		delete *iter;
	}
	for (list<pessoas *>::iterator iter = LPessoas.begin();
		iter != LPessoas.end(); ++iter)
	{
		delete *iter;
	}
	/*duvida*/
	for (int i = 0; i < row; ++i)
		delete[] matriz[i];
	delete[] matriz;
}

void grafos::Mostrar()
{
	for (list<pessoas *>::iterator P = LPessoas.begin();
		P != LPessoas.end(); ++P)
	{
		(*P)->Mostrar();
	}
	cout << "\n\n\n\n\n\n\n\n" << endl;

	for (list<fronteira *>::iterator P = LF.begin();
		P != LF.end(); ++P)
	{
		(*P)->Mostrar();
	}

	cout << "\n\n\n\n\n\n\n\n" << endl;

	for (list<aresta *>::iterator P = LAresta.begin();
		P != LAresta.end(); ++P)
	{
		(*P)->Mostrar();
	}
}

//-------------------------------------------------------------------
//Método: Load
//Parametros:
// Entrada:
//     fich_grafos: Ficheiro dos dados do grafos
//     fich_pessoas: Ficheiro das pessoas que querem fazer as viagens entre as fronteiras
// Retorno:
//    true/false, mediante a leitura correcta!
//-------------------------------------------------------------------

bool grafos::Load(const string &fich_grafos, const string &fich_pessoas)
{	
	 ifstream file(fich_grafos);
	 string str_grafo;
	 char split_char = ';';
	 string limite = "//-------------------";

	 int id = 0;
	 int x = 0;
	 int y = 0;
	 int tipo;

	 int origem = 0;
	 int destino = 0;
	 int custo = 0;

	 while (getline(file, str_grafo))
	 {
		 if (str_grafo.size() <= 2)
		 {
			 cout << "OK" << endl;
		 }
		 else {

			 if (str_grafo.compare(limite) != 0) {
				 istringstream split(str_grafo);
				 vector<string> tokens;
				 for (string each; getline(split, each, split_char); tokens.push_back(each));
				 {
					 id = stoi(tokens[0]);
					 x = stoi(tokens[1]);
					 y = stoi(tokens[2]);
					 tipo = stoi(tokens[3]);
					 
					 if (tipo == 1)
					 {
						 LF.push_back(new tipo1(id, x, y, 1));
					 }

					 else if (tipo == 2) {
						 LF.push_back(new Tipo2(id, x, y, 2));
					 }
					 else {
						 LF.push_back(new oficial(id, x, y, 3));
					 }
				 }
			 }
			 else {
				 while (getline(file, str_grafo))
				 {

					 istringstream split(str_grafo);
					 vector<string> tokens;
					 for (string each; getline(split, each, split_char); tokens.push_back(each));
					 {

						 origem = stoi(tokens[0]);
						 destino = stoi(tokens[1]);
						 custo = stoi(tokens[2]);

						 LAresta.push_back(new aresta(origem, destino, custo));

					 }
					
				 }
			 }
		 }

	 }

	 ifstream file2(fich_pessoas);

	 int id_pessoa;
	 string nome;
	 int v_partida;
	 int v_chegada;
	 string str_pessoa;

	 while (getline(file2, str_pessoa))
	 {

		 istringstream split(str_pessoa);
		 vector<string> tokens;
		 for (string each; getline(split, each, split_char); tokens.push_back(each));
		 {

			 id_pessoa = stoi(tokens[0]);
			 nome = tokens[1];
			 v_partida = stoi(tokens[2]);
			 v_chegada = stoi(tokens[3]);

			 LPessoas.push_back(new pessoas(id_pessoa, v_partida, v_chegada, nome));
		 }
	 }
	 cout << "Carregou" << endl;

	
	
	return true;
}

void grafos::GrafoToMatriz() {
	int inc = 1;
	row = ContarNos();
	matriz = new int *[row];
	
	
	for (int i = 0; i < row; i++)
	{
		matriz[i] = new int[row];		
		for (int j = 0; j < row; j++)		
		{
			if (i == j)
				matriz[i][j] = 0;
			else
				matriz[i][j] = INFINITY;
		}
	}
	for (list<aresta *>::iterator P = LAresta.begin();
		P != LAresta.end(); ++P)
	{
		matriz[(*P)->_inicio][(*P)->_Fim] = (*P)->_valor;
	}
	

}

int grafos::ContarNos()
{
	int count = 0;
	for (list<fronteira *>::iterator P = LF.begin();
		P != LF.end(); ++P)
	{
		//(*P)->Mostrar();
		count++;

	}
	cout << "Contei estas fronteira: " << count << endl;
	return count;
}

int grafos::ContarArcos()
{
	int count = 0;

	for (list<aresta *>::iterator P = LAresta.begin();
		P != LAresta.end(); ++P)
	{
		//(*P)->Mostrar();
		count++;
	}
	cout << "Contei estas arestas: " << count << endl;
	return count;
}

int grafos::Memoria()
{
	double count=0;
	count = sizeof(grafos);
	for (list<fronteira *>::iterator iter = LF.begin();
		iter != LF.end(); ++iter)
	{
		count +=sizeof( *iter);
		count += (*iter)->MemoriaF();
	}
	for (list<aresta *>::iterator iter = LAresta.begin();
		iter != LAresta.end(); ++iter)
	{
		count += sizeof(*iter);
		count += (*iter)->MemoriaA();
	}
	for (list<pessoas *>::iterator iter = LPessoas.begin();
		iter != LPessoas.end(); ++iter)
	{
		count += sizeof(*iter);
		count += (*iter)->memoriaP();
	}
	
	cout << count << endl;
	return count;
}

list<int>* grafos::NoMaisArcos()
{
	int big = 0;
	list<int> ids;
	list<int> *fim = new list<int>();
	map<int, int> bar;
	list<int>::iterator it;
	map<int, int>::iterator it_2;
	for (list<aresta *>::iterator I = LAresta.begin();
		I != LAresta.end(); ++I)
	{
		ids.push_back((*I)->_Fim);
		ids.push_back((*I)->_inicio);
	}
	ids.sort();
	

    for (auto const &f : ids)
        bar[f]++;

		
		for (it_2 = bar.begin(); it_2 != bar.end(); it_2++) {
			if (it_2->second > big)
			{
				big = it_2->second;
				fim->clear();
				fim->push_back(it_2->first);
			}
			else if (it_2->second == big)
			{
				fim->push_back(it_2->first);

			}
			
		}

	
		for (list<int>::iterator P = fim->begin();
			P != fim->end(); ++P)
		{

			cout << *P << endl;

		}
               
	return fim;

}

bool grafos::Adjacencia(int v1, int v2)
{

	for (list<aresta *>::iterator P = LAresta.begin();
		P != LAresta.end(); ++P)
	{
		if ((*P)->_inicio == v1)
		{
				if ((*P)->_Fim == v2)
				{
					cout << " adj " << endl;
					return true;
				}
		}
		if ((*P)->_inicio == v2)
		{
			if ((*P)->_Fim == v1)
			{
				cout << " adj " << endl;
				return true;
			}
		}
	}
	cout << "nao adj " << endl;
	return false;
}


list<int>* grafos::VerticesIsolados()
{
	list<int> ids ;
	
	list<int> *a = new list<int>();
	
		for (list<aresta *>::iterator I = LAresta.begin();
			I != LAresta.end(); ++I)
		{
						ids.push_back((*I)->_Fim);
						ids.push_back((*I)->_inicio);
		}


		for (list<fronteira *>::iterator P = LF.begin();
			P != LF.end(); ++P)
		{
			bool found = (find(ids.begin(), ids.end(), (*P)->_id) != ids.end());
			if (!found) {
				a->push_back((*P)->_id);
			}
		}
	for (list<int>::iterator P = a->begin();
		P != a->end(); ++P)
	{
		
			cout << *P <<" -> Isolado!"<< endl;
		
	}
	return a;
}

bool grafos::Search(int v)
{
	list<int> helper;

	for (list<fronteira *>::iterator I = LF.begin();
		I != LF.end(); ++I)
	{
		helper.push_back((*I)->_id);
	}

	bool found = (find(helper.begin(), helper.end(), v) != helper.end());
	cout << found << endl;
	return found;
}

bool grafos::RemoverVertice(int v)
{
	for (list<aresta *>::iterator P = LAresta.begin();
		P != LAresta.end(); ++P)
	{
		if ((*P)->_inicio == v) {
			LAresta.erase(P);
			break;
		}
	}

	for (list<aresta *>::iterator F = LAresta.begin();
		F != LAresta.end(); ++F)
	{
		if ((*F)->_Fim == v) {
			LAresta.erase(F);
			break;
		}
	}

	for (list<fronteira *>::iterator I = LF.begin();
		I != LF.end(); ++I)
	{
		if ((*I)->_id == v) {
			LF.erase(I);
			break;
		}
	}
	//Mostrar();
	return false;

}

bool grafos::RemoverAresta(int v1, int v2)
{
	for (list<aresta *>::iterator P = LAresta.begin();
		P != LAresta.end(); ++P)
	{
		if ((*P)->_inicio == v1 && (*P)->_Fim==v2) {
			LAresta.erase(P);
			break;
		}
	}
	Mostrar();
	return false;
}

void grafos::EscreverXML(const string & s)
{
	ofstream F(s);
	
	for (list<fronteira*>::iterator P = LF.begin();
		P != LF.end(); ++P)
	{
		(*P)->GravarXML(F);
	}
	
	for (list<aresta*>::iterator A = LAresta.begin();
		A != LAresta.end(); ++A)
	{
		(*A)->GravarXML(F);
	}
	
	for (list<pessoas*>::iterator I = LPessoas.begin();
		I != LPessoas.end(); ++I)
	{
		(*I)->GravarXML(F);
	}
	F.close();
}

bool grafos::LerXML(const string & s)
{
		string line;

		int id = 0;
		int x = 0;
		int y = 0;
		int tipo = 0;

		int origem = 0;
		int destino = 0;
		int custo = 0;

		int idi = 0;
		string nome;
		int inicio = 0;
		int fim = 0;
		ifstream file(s);

		if (file.is_open())
		{
			getline(file, line);
			while (getline(file, line))
			{
				if (line == "0")
				{
				}
				else if (line == "<FRONTEIRA>")
				{
					while (getline(file, line))
					{
						if (line == "</FRONTEIRA>")
						{
							if (tipo == 1)
							{
								LF.push_back(new tipo1(id, x, y,  1));
							}
							else if (tipo == 2)
							{
								LF.push_back(new Tipo2(id, x, y,  2));
							}
							else if (tipo == 3)
							{
								LF.push_back(new oficial(id, x, y, 3));
							}
							break;
						}
						else
						{
							if (line == "<ID>")
							{
								while (getline(file, line))
								{
									if (line == "</ID>")
									{
										break;
									}
									else
									{
										id = stoi(line);
									}
								}

							}
							if (line == "<X>")
							{
								while (getline(file, line))
								{
									if (line == "</X>")
									{
										break;
									}
									else
									{
										x = stoi(line);
									}
								}
							}
							if (line == "<Y>")
							{
								while (getline(file, line))
								{
									if (line == "</Y>")
									{
										break;
									}
									else
									{
										y = stoi(line);
									}

								}
							}
							if (line == "<TIPO>")
							{
								while (getline(file, line))
								{
									if (line == "</TIPO>")
									{
										break;
									}
									else
									{
										tipo = stoi(line);
									}
								}
							}
						}

					}
				}

			}
			file.close();
		}
		string linee;
		file.open(s);
		if (file.is_open())
		{
			getline(file, linee);
			while (getline(file, linee))
			{
				if (linee == "0")
				{
				}
				else if (linee == "<ARESTAS>")
				{
					while (getline(file, linee))
					{
						if (linee == "</ARESTAS>")
						{
							for (list<fronteira *>::iterator it = LF.begin(); it != LF.end(); ++it)
							{
								if (origem == (*it)->_id)
								{
									LAresta.push_back(new aresta(origem, destino, custo));
								}
							}
						}
						else
						{
							if (linee == "<ORIGEM>")
							{
								while (getline(file, linee))
								{
									if (linee == "</ORIGEM>")
									{
										break;
									}
									else
									{
										origem = stoi(linee);
									}
								}

							}
							if (linee == "<DESTINO>")
							{
								while (getline(file, linee))
								{
									if (linee == "</DESTINO>")
									{
										break;
									}
									else
									{
										destino = stoi(linee);
									}
								}
							}
							if (linee == "<CUSTO>")
							{
								while (getline(file, linee))
								{
									if (linee == "</CUSTO>")
									{
										break;
									}
									else
									{
										custo = stoi(linee);;
									}

								}
							}
						}

					}
				}

			}
			file.close();
		}

		string lineee;
		file.open(s);
		if (file.is_open())
		{
			getline(file, lineee);
			while (getline(file, lineee))
			{
				if (lineee == "0")
				{
				}
				else if (lineee == "<PESSOA>")
				{
					cout << "Entrei dentro de PESSOA" << endl;
					while (getline(file, lineee))
					{
						if (lineee == "</PESSOA>")
						{
							LPessoas.push_back(new pessoas(idi, inicio, fim, nome));
						}
						else
						{
							if (lineee == "<IDPESSOA>")
							{
								while (getline(file, lineee))
								{
									if (lineee == "</IDPESSOA>")
									{
										break;
									}
									else
									{
										idi = stoi(lineee);
									}
								}

							}
							if (lineee == "<NOME>")
							{
								while (getline(file, lineee))
								{
									if (lineee == "</NOME>")
									{
										break;
									}
									else
									{
										nome = lineee;
									}
								}
							}
							if (lineee == "<INICIO>")
							{
								while (getline(file, lineee))
								{
									if (lineee == "</INICIO>")
									{
										break;
									}
									else
									{
										inicio = stoi(lineee);
									}

								}
							}
							if (lineee == "<FIM>")
							{
								while (getline(file, lineee))
								{
									if (lineee == "</FIM>")
									{
										break;
									}
									else
									{
										fim = stoi(lineee);
									}

								}
							}
						}

					}
				}

			}
			file.close();
		}
		return true;
	}


list<int>* grafos::DevolveVerticesTipo(const string & tipo)
{
    int tipoInt=stoi(tipo);
	
	list<int> *dev = new list<int>();
	for (list<fronteira *>::iterator I = LF.begin();
		I != LF.end(); ++I)
	{
		if ((*I)->_tipo == tipoInt) {
			dev->push_back((*I)->_id);
			
		}
		
	}
	for (list<int>::iterator P = dev->begin();
		P != dev->end(); ++P)
	{

		cout << *P  <<" Fronteiras de Tipo:"<< tipo << endl;

	}

	return dev;
}

/*********************************************************************/

int grafos::MinDistance(int* dist, int* Blackened)
{
	int min = INFINITY, min_index, v;
	for (v = 0; v < n; v++)
		if (!Blackened[v] && dist[v] < min) {
			min = dist[v];
			min_index = v;
		}
	return min == INFINITY ? INFINITY : min_index;
}

// Function to print the path 
void grafos::PrintPath(int* parent, int _d)
{

	if (parent[_d] == NILL) {
		cout << _d;
		pathi->push_back(_d);
		return;
	}
	PrintPath(parent, parent[_d]);
	cout << "->" << _d;
}

void grafos::Dijkstra(int **Graph, int _n, int _s, int _d)
{
	
	
	int i, u, v, count;
	int dist[n];
	int Blackened[n] = { 0 };
	int pathlength[n] = { 0 };
	int parent[n];

	// The parent Of the source vertex is always equal to nill 
	parent[_s] = NILL;

	// first, we initialize all distances to infinity. 
	for (i = 0; i < n; i++)
		dist[i] = INFINITY;

	dist[_s] = 0;
	for (count = 0; count < n - 1; count++) {
		u = MinDistance(dist, Blackened);
		// if MinDistance() returns INFINITY, then the graph is not 
		// connected and we have traversed all of the vertices in the 
		// connected component of the source vertex, so it can reduce 
		// the time complexity sometimes 
		// In a directed graph, it means that the source vertex 
		// is not a root 
		if (u == INFINITY)
			break;
		else {
			
			// Mark the vertex as Blackened 
			Blackened[u] = 1;
			for (v = 0; v < n; v++) {
				if (!Blackened[v] && Graph[u][v]
					&& dist[u] + Graph[u][v] < dist[v]) {
					parent[v] = u;
					pathlength[v] = pathlength[parent[v]] + 1;
					dist[v] = dist[u] + Graph[u][v];
				}
				else if (!Blackened[v] && Graph[u][v]
					&& dist[u] + Graph[u][v] == dist[v]
					&& pathlength[u] + 1 < pathlength[v]) {
					parent[v] = u;
					pathlength[v] = pathlength[u] + 1;
				}
			}
		}
	}

	// Printing the path 
	if (dist[_d] != INFINITY)
		PrintPath(parent, _d);
	else
		cout << "There is no path between vertex "
		<< _s << "to vertex " << _d;
}



list<int>* grafos::Caminho(int v1, int v2 , double & custo_total)
{
	
	Dijkstra(matriz, ContarNos(), v1, v2);
	return pathi;
}

list<int>* grafos::CaminhoMinimo(int v1, int v2, double & custo_total)
{
	
	
	Dijkstra(matriz, ContarNos(), v1, v2);
	
	return pathi;
}



