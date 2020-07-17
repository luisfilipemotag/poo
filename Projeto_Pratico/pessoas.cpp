#include "pch.h"
#include "pessoas.h"

using namespace std;

pessoas::pessoas(int idP, int Finicio, int Ffim, string Nome)
{
	_idP = idP;
	_Finicio = Finicio;
	_Ffim = Ffim;
	_Nome = Nome;

	
}


pessoas::~pessoas()
{
}

void pessoas::Mostrar()
{
	cout << _idP << _Finicio << _Ffim << _Nome << endl;

}
int pessoas::memoriaP()
{
	return sizeof(_idP) + sizeof(_Finicio) + sizeof(_Ffim) + sizeof(_Nome);
}
void pessoas::GravarXML(ofstream &fi)
{
	fi <<"<PESSOA>\n\t<ID>"<< _idP << "</ID>\n\t<INICIO> "<< _Finicio <<"</INICIO>\n\t<FIM>" <<_Ffim <<"</FIM>\n\t<NOME>" << _Nome <<"</NOME>\n</PESSOA>"<< endl;
}