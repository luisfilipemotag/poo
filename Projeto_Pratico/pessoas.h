#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
using namespace std;
class pessoas
{
public:
	int _idP, _Finicio, _Ffim;
	string _Nome;
	pessoas() {};
	pessoas(int idP, int Finicio, int Ffim,const string Nome);
	~pessoas();
	virtual void Mostrar();
	virtual int memoriaP();
	void GravarXML(ofstream & fi);
};

