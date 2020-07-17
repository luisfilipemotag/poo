#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <sstream>
#include <algorithm>
#include <map>
#include <list>
#include "aresta.h"
#include "pessoas.h"
#include "fronteira.h"
#include "tipo1.h"
#include "Tipo2.h"
#include "oficial.h"
using namespace std;


class grafos
{
public:
 
	list<pessoas*> LPessoas;
	list<aresta*> LAresta;
	list<fronteira*> LF;
	#define INFINITY 9999 
	#define NILL -1 
	#define n 25
	int **matriz;
	list<int> *pathi = new list<int>();
	int row = ContarNos();
	


	
	
	grafos();
	//Implemente o destrutor do grafos;
	~grafos();
	void Mostrar();
	void GrafoToMatriz();
	//Carregar os dados de ficheiros (do grafos e de pessoas);
	bool Load(const string &fich_grafos, const string &fich_pessoas);
	//Contar o n�mero de n�s/fronteiras do grafos;
	int ContarNos();
	
	//Contar o n�mero de arestas/arcos do grafos;
	int ContarArcos();

	//Determinar toda a mem�ria ocupada;
	int Memoria();
	
	//Determinar qual o n�/fronteira que tem mais arcos/aresta, se existirem v�rios devolve uma lista deles;
	list<int> *NoMaisArcos();
	
	//Verificar se um n� � adjacente de outro n� do grafos;
	bool Adjacencia(int v1, int v2);
	
	//Determinar um caminho(n�o interessa se � o mais r�pido!, � qualquer um!) de um n�/fronteira para outro.... //devolvendo o custo total;
	list<int> *Caminho(int v1, int v2, double &custo_total);

	//Determinar quais os v�rtices que est�o isolados (Um v�rtice � isolado se n�o existe nenhum caminho at� ele!);
	list<int> *VerticesIsolados();
	
	//Verificar se um dado v�rtice existe
	bool Search(int v);
	
	//Remover um dado v�rtice, tamb�m ser� necess�rio remover todas as arestas;
	bool RemoverVertice(int v);
	
	//Remover a aresta que liga 2 v�rtices;
	bool RemoverAresta(int v1, int v2);
	
	//Gravar para ficheiro em formato XML todas as informa��es do grafos;
	void EscreverXML(const string &s);
	
	//Ler de um ficheiro em formato XML todo o grafos (antes de ler deve ser apagado tudo o que estiver no grafos); Se leu corretamente devolve //true, sen�o devolve false;
	bool LerXML(const string &s);
	//Devolver uma lista de todos os v�rtices/fronteiras de um dado tipo;
	list<int> *DevolveVerticesTipo(const string &tipo);
	
	//Determinar o caminho m�nimo entre 2 n�s, devolvendo o custo total;
	list<int> *CaminhoMinimo(int v1, int v2, double &custo_total);
	
	//Determinar o caminho m�ximo entre 2 n�s (passando somente uma vez em cada v�rtice), devolvendo o custo total;
	list<int> *CaminhoMaximo(int v1, int v2, double &custo_total)
	{
		return NULL;
	}
	//Ser� poss�vel ir de uma fronteira(v1) a outra(v2), passando somente por fronteiras de um dado tipo?
	bool PossivelCaminho(int v1, int v2, int TipoFronteira)
	{
		return false;
	}
	//Assumindo que todas as pessoas (do ficheiro) andaram em viagem, qual foi a fronteira com menos tr�fego/visitas? (No caso de serem v�rias,// deve devolver uma lista com as fronteiras);
	void FronteirasMenosVisitadas(list<int> &Lv)
	{

	}

	//Dada uma fronteira (v1), determinar todas as fronteiras onde n�o � poss�vel chegar apartir de v1. Deve devolver uma lista dessas fronteiras!;
	void SitiosInacessiveisAPartirDe(int V1, list<int> &Lv)
	{

	}
	int MinDistance(int* dist, int* Blackened);
	void PrintPath(int* parent, int _d);
	void Dijkstra(int **Graph, int _n, int _s, int _d);
};

