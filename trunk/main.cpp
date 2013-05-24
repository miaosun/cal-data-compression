/*
 * main.cpp
 *
 *  Created on: 17 de Mai de 2013
 *      Author: Reis
 */

#include "Encoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>

bool isDigit(const string& s)
{
	istringstream i(s);
	int temp;
	return ( (i >> temp) ? true : false );
}

int intinput()
{
	string s;
	int i=0;
	fflush(stdin);
	getline(cin, s);
	fflush(stdin);
	while(!isDigit(s))
	{
		cout<<"Invalido, tenta novamente:\nOpcao: ";
		getline(cin, s);
		fflush(stdin);
	};

	i = atoi(s.c_str());
	return i;
}

void menuComprimir()
{
	int op;
	string filename;
	ifstream f;
	cout<<"-----------Compressao Ficheiro-----------------"<<endl<<endl;
	cout<<"Inserir o nome do ficheiro quer comprimir: "<<endl;
	getline(cin, filename);
	f.open(filename.c_str());
	if(!f.is_open())
		cout<<"Nao conseguiu abrir ficheiro "<<filename<<" !! Tenta novamente!"<<endl<<endl;
	else
	{
		f.close();
		cout<<"\nEscolha um algoritmo:"<<endl;
		cout<<"\t1: Keyword Encoding"<<endl;
		cout<<"\t2: Huffman"<<endl;
		cout<<"\t3: Lempel每Ziv每Welch"<<endl;

		do{
			cout<<"Opcao: ";
			op = intinput();
			if(op!=1 && op!=2 && op!=3)
				cout<<"Invalido, tenta novamente: "<<endl;
		}while(op!=1 && op!=2 && op!=3);

		switch(op)
		{
		case 1:
		{
			KeywordEncoding k;
			k.comecaComprimir(filename);
			break;
		}
		case 2:
		{
			HuffmanCode huffman;
			huffman.comprimir(filename);
			break;
		}
		case 3:	//lzw
		{
			break;
		}
		default:
		{
			cout<<"Invalido, tenta novamente: "<<endl;
			break;
		}
		}
	}
}

void menuDescomprimir()
{
	int op;
	string filename, padrao;
	ifstream f;
	cout<<"-----------Descompressao Ficheiro-----------------"<<endl<<endl;
	cout<<"Inserir o nome do ficheiro quer descomprimir: "<<endl;
	getline(cin, filename);
	f.open(filename.c_str());
	if(!f.is_open())
		cout<<"Nao conseguiu abrir ficheiro "<<filename<<" !! Tenta novamente!"<<endl<<endl;

	else
	{
		f.close();
		cout<<"\nEscolha um algoritmo:"<<endl;
		cout<<"\t1: Keyword Encoding"<<endl;
		cout<<"\t2: Huffman"<<endl;
		cout<<"\t3: Lempel每Ziv每Welch"<<endl;

		do{
			cout<<"Opcao: ";
			op = intinput();
			if(op!=1 && op!=2 && op!=3)
				cout<<"Invalido, tenta novamente: "<<endl;
		}while(op!=1 && op!=2 && op!=3);

		switch(op)
		{
		case 1:
		{
			KeywordEncoding k;
			padrao = filename.substr(filename.find("]")+1) + ".key";
			k.descomprimir(filename, padrao);
			break;
		}
		case 2:
		{
			HuffmanCode huffman;
			huffman.descomprimir(filename);
			break;
		}
		case 3: //lzw
		{
			break;
		}
		default:
		{
			cout<<"Invalido, tenta novamente: "<<endl;
			break;
		}
		}
	}
}

void menuPrincipal()
{
	while(1) {
		int op;
		cout<<"-----------Data Compression-----------------"<<endl;
		cout<<"1: Comprimir ficheiro"<<endl;
		cout<<"2: Descomprimir ficheiro"<<endl<<endl;
		cout<<"0: Sair"<<endl<<endl;

		do{
			cout<<"Opcao: ";
			op = intinput();
			if(op!=0 && op!=1 && op!=2)
				cout<<"Invalido, tenta novamente: "<<endl;
		}while(op!= 0 && op!=1 && op!=2);

		switch(op)
		{
		case 1:
			menuComprimir();
			break;
		case 2:
			menuDescomprimir();
			break;
		case 0:
			exit(0);
		default:
			cout<<"Invalido, tenta novamente: "<<endl;
			break;
		}
	}
}


int main() {

	/* teste LZW
	string filename = "abc.txt";
	string resposta;

	LZW a(filename);

	a.comprimir(filename);

	a.guardarDicionario();

	cout << "Quer descomprimir?" << endl;
	cin >> resposta;

	if (resposta == "sim") {
		a.lerDicionario("dicionario.txt");
		a.descomprimir("saidaLZW.txt");
	}

	 */

	menuPrincipal();
	cout << "Exiting..." << endl;
	return 0;
}
