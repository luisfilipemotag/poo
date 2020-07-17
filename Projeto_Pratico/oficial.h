#pragma once
#include "fronteira.h"
class oficial :
	public fronteira
{
public:
	oficial(int id, int x, int y, int tipo);
	~oficial();
	int getpais() {return 3;}
};

