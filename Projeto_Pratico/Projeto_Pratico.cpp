// Projeto_Pratico.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
using namespace std;

#include "grafos.h"
double custo_total;
int main()
{
	cout << "Inicio do Programa" << endl;
	
		grafos *GF;

		GF = new grafos();
		GF->Load("grafo_2.txt", "pessoas.txt");
		GF->GrafoToMatriz();
		//GF->ContarNos();
		//GF->ContarArcos();
		//GF->Memoria();
		//GF->NoMaisArcos();
		//GF->Adjacencia(1, 3);
		//GF->Caminho(12, 16,custo_total);
		//GF->VerticesIsolados();
		//GF->Search(3);
		//GF->RemoverVertice(13);
		//GF->RemoverAresta(13, 10);
		//GF->EscreverXML("eu.xml");
		//GF->LerXML("eu.xml"); //n trabalha corretamente
		//GF->DevolveVerticesTipo("2");
		GF->CaminhoMinimo(3, 6, custo_total);

		delete GF;

		return 1;
	
}
