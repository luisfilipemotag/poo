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


class fronteira
{
public:
	int _id, _x, _y, _tipo;
	fronteira() {};
	fronteira(int id, int x, int y,int tipo);
	~fronteira();
	
	virtual void Mostrar();
	virtual int MemoriaF();
	void GravarXML(ofstream & fi);
	
};

