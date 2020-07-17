#include "pch.h"
#include "Fronteira.h"
using namespace std;


fronteira::fronteira(int id , int x,int y, int tipo)
{
	_id =id;
	_x = x;
	_y = y;
	_tipo = tipo;
	
}


fronteira::~fronteira()
{
	
}



void fronteira::Mostrar()
{
	cout <<"id: "<< _id <<" tipo: "<< _tipo <<" Inicio: "<< _x <<" Fim: "<< _y << endl;
	
}
int fronteira::MemoriaF()
{
//	return sizeof(_id)+ sizeof(_tipo)+ sizeof(_x)+ sizeof(_y);
	return sizeof(*this);
}
void fronteira::GravarXML(ofstream &fi)
{
	fi << "<FRONTEIRA>\n\t<ID>" << _id << "</ID>\n\t<TIPO>" << _tipo << "<\TIPO>\n\t<INICIO> " << _x << "</INICIO>\n\t<FIM>" << _y <<"</FIM>\n</FRONTEIRA>"<< endl;
}