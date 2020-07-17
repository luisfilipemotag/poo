#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
#include <list>
class aresta
{
public:
	int _inicio, _Fim, _valor;
	aresta(int Inicio ,int Fim, int valor);
	~aresta();
	void Mostrar();
	int MemoriaA();
	void GravarXML(ofstream & fi);
};

