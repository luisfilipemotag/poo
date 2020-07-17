#pragma once
#include "fronteira.h"
#include <string>
using namespace std;
class tipo1 : public fronteira
{
public:
	tipo1(int id, int x, int y, int tipo);
	~tipo1();
	int getpreco() { return 20 ; }
	
};

