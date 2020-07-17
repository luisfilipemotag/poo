#include "pch.h"
#include "aresta.h"


aresta::aresta(int Inicio, int Fim, int Valor)
{
	_inicio = Inicio;
	_Fim = Fim;
	_valor = Valor;
	
}


aresta::~aresta()
{
}

void aresta::Mostrar()
{
	cout << "inicio: "<<_inicio <<" Fim:"<< _Fim <<" Valor: "<< _valor  << endl;

}

int aresta::MemoriaA()
{
	
	return sizeof(_inicio) + sizeof(_Fim) + sizeof(_valor);
}

void aresta::GravarXML(ofstream &fi)
{
	fi << "<ARESTA>\n\t<INICIO>" << _inicio << "</INICIO>\n\t<FIM>" << _Fim << "</FIM>\n\t<VALOR>" << _valor <<"</VALOR>\n</ARESTA>"<< endl;
}