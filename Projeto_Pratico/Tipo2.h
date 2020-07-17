#pragma once
#include "fronteira.h"
class Tipo2 :
	public fronteira
{
public:
	Tipo2(int id, int x, int y, int tipo);
	~Tipo2();
	int getpeso() { return 1; }
};

