/*
 * 	FICHEIRO: main.cpp
 *	PROJECTO: Projecto2 CAL - Data Compression (T2)
 *  TURMA / GRUPO: Turma 2MIEIC2 / Grupo D
 *  AUTORES:
 *  - Jorge Miguel Reis
 *  - Miao Sun
 *  - Vitor Castro
 */

#include "Encoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>

map<string, int> dicionarioLZW;

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
	system("cls");
	cout<<"-----------Compressao Ficheiro-----------------"<<endl<<endl;
	cout<<"Inserir o nome do ficheiro a comprimir: "<<endl;
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
		cout<<"\t3: Lempel-Ziv-Welch"<<endl;

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
			LZW lzw;
			lzw.comprimir(filename);

			dicionarioLZW = lzw.getDicCompressao();
			lzw.setDicCompressao(dicionarioLZW);
			//lzw.guardarDicionario();
			//			lzw.lerDicionario("dicionario.txt");
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
	system("cls");
	cout<<"-----------Descompressao Ficheiro-----------------"<<endl<<endl;
	cout<<"Inserir o nome do ficheiro a descomprimir: "<<endl;
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
		cout<<"\t3: Lempel-Ziv-Welch"<<endl;

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
			if(filename.substr(filename.length()-3,3)!=".ke")
				throw Exception("\nFicheiro nao valido!\n");
			KeywordEncoding k;
			string padrao = filename;
			padrao.resize(filename.length()-2);
			padrao=padrao+"txt.key";
			k.descomprimir(filename, padrao);
			break;
		}
		case 2:
		{
			if(filename.substr(filename.length()-3,3)!=".hf")
				throw Exception("\nFicheiro nao valido!\n");
			HuffmanCode huffman;
			huffman.descomprimir(filename);
			break;
		}
		case 3: //lzw
		{
			if(filename.substr(filename.length()-4,4)!=".lzw")
				throw Exception("\nFicheiro nao valido!\n");
			LZW lzw;
			//lzw.lerDicionario("dicionario.txt");
			//dicionarioLZW = lzw.getDicCompressao();
			lzw.setDicCompressao(dicionarioLZW);
			lzw.descomprimir(filename);
			break;

		}
		default:
		{
			cout<<"\nInvalido, tenta novamente: "<<endl;
			break;
		}
		}
	}
}

void menuPrincipal()
{
	while(1) {
		int op;
		system("cls");
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
			system("pause");
			break;
		case 2:
			try{
				menuDescomprimir();
			}
			catch(Exception &e) {
				cout << e.getMessage() << endl;
			}
			system("pause");
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

	menuPrincipal();
	cout << "Exiting..." << endl;
	return 0;
}
