/*
 * 	FICHEIRO: huffmanCode.cpp
 *	PROJECTO: Projecto2 CAL - Data Compression (T2)
 *  TURMA / GRUPO: Turma 2MIEIC2 / Grupo D
 *  AUTORES:
 *  - Jorge Miguel Reis
 *  - Miao Sun
 *  - Vitor Castro
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Encoder.h"

#define MASK 0x80

using namespace std;

bool compareNodes(Node* n1, Node* n2) {
	return n1->getFreq() < n2->getFreq();
}

HuffmanCode::HuffmanCode() { }

void HuffmanCode::initFreqs() {
	for(unsigned int i=0; i<256; i++)
		freqs[i]=0;
}

void HuffmanCode::calculaFreqs() {
	initFreqs();
	int c;
	ifstream file(filename.c_str());
	if(file.is_open()) {
		while(!file.eof()) {
			if(c!=EOF) {
				c=file.get();
				freqs[c]++;
			}
		}
		freqs[3]++; //caracter ETX (end of text)
		file.close();
	}
}

Node* HuffmanCode::buildTree() {
	vector<Node*> btree; //vector no (arvore)
	for(unsigned int i=0; i<256; i++) {
		if (freqs[i]>0) {
			Node* n = new Node((unsigned char) i, freqs[i]);
			btree.push_back(n);
		}
	}
	sort(btree.begin(),btree.end(),compareNodes); //ordena por ordem crescente de frequencias

	while (btree.size() > 1) {
		Node* parent= new Node(); // novo no
		parent->setLeft(btree[0]);
		parent->setRight(btree[1]);
		parent->setFreq(btree[0]->getFreq()+btree[1]->getFreq()); //soma frequencias das folhas
		btree.erase(btree.begin());
		btree.erase(btree.begin());
		btree.push_back(parent); //insere novo no no vector
		sort(btree.begin(),btree.end(),compareNodes); //reordena vector
	}
	return btree[0];
}

void HuffmanCode::geraReprBinaria(Node* n, string s, vector<string> &v) {
	if(n->isLeaf()) {
		v[(int)n->getCaracter()]=s;
	}
	else {
		if(n->getLeft()!=NULL)
			geraReprBinaria(n->getLeft(),s+"0",v);
		if(n->getRight()!=NULL)
			geraReprBinaria(n->getRight(),s+"1",v);
	}
}

void HuffmanCode::geraFicheiroCodificacao(vector<string> r) {
	string f = filename;
	f.resize(filename.length()-3);
	f=f+"hfc";
	ofstream codfile(f.c_str());
	if(codfile.is_open()) {
		for(unsigned int i=0; i<256; i++) {
			if(freqs[i]>0) {
				codfile << i << endl;
				codfile << freqs[i] << endl;
			}
		}
		codfile.close();
	}
	else
		cout << "Erro na escrita do ficheiro de informacao da codificacao!" << endl;

}

void HuffmanCode::comprimir(string file) {

	system("cls");
	cout << "A comprimir ficheiro..." << endl;

	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	filename=file;
	int c;
	string temp;
	vector<unsigned char> codBinaria;
	vector<string> repr(256,"");

	calculaFreqs(); //calcula frequencias
	Node* root = buildTree(); //constroi avore

	geraReprBinaria(root,"",repr); //gera vector com as representacoes
	geraFicheiroCodificacao(repr); //gera ficheiro com a codificacao utilizada

	//nome do ficheiro de saida com extensao .hf
	string codedFilename = filename;
	codedFilename.resize(filename.length()-3);
	codedFilename=codedFilename+"hf";

	//cria uma string de '0's e '1's com as representacoes dos caracteres do texto
	ifstream originalFile(filename.c_str());
	if(originalFile.is_open()) {
		while(!originalFile.eof()) {
			c=originalFile.get();
			if(c!=EOF) {
				temp+=repr[c];
			}
		}
		originalFile.close();
		temp+=repr[3]; //caracter ETX (end of text) para marcar fim do texto

		//cria codificacao binaria para tdo o texto (vector com elementos de 8bits)
		for(unsigned int i=0; i<temp.size();i=i+8) {
			unsigned char byte=0;
			for(unsigned int j=0; j<8;j++) {
				byte=byte<<1;
				if(i+j < temp.size() && temp[i+j]=='1')
					byte=byte|1;
			}
			codBinaria.push_back(byte);
		}
	}

	//grava a informacao codificada (binaria) no ficheiro de saida
	ofstream codedfile(codedFilename.c_str(),ios_base::binary);
	for (unsigned int k=0;k<codBinaria.size();k++) {
		char out=codBinaria[k];
		codedfile.write(&out,1);
	}
	codedfile.close();
	cout << "Ficheiro Comprimido!" << endl;

	gettimeofday(&tv2, NULL);

	printf("Tempo Total de Compressao:  = %f segundos\n",
			(double) (tv2.tv_usec - tv1.tv_usec) / 1000000
			+ (double) (tv2.tv_sec - tv1.tv_sec));
}

void HuffmanCode::lerFicheiroCodificacao(string file) {
	ifstream cfile(file.c_str());
	int c;
	int f;
	if(cfile.is_open()) {
		while(!cfile.eof()) {
			fflush(stdin);
			cfile >> c;
			fflush(stdin);
			cfile >> f;
			freqs[c]=f;
		}
		cfile.close();
	}
	else cout << "Impossivel abrir ficheiro auxiliar com frequencias!" << endl;
}

void HuffmanCode::descomprimir(string inFilename) {
	initFreqs();

	string cfile = inFilename;
	cfile.resize(inFilename.length()-2);
	cfile=cfile+"hfc";

	lerFicheiroCodificacao(cfile);
	Node *root = buildTree();

	string outFilename = inFilename;
	outFilename.resize(inFilename.length()-3);
	outFilename=outFilename+"DESC.txt";

	ifstream inFile(inFilename.c_str(),ios_base::binary);

	cout << "A descomprimir..." << endl;

	if(inFile.is_open()) {
		ofstream outFile(outFilename.c_str());
		if(outFile.is_open()) {
			Node* actualNode=root;
			bool fim=false;
			char codchar=-1;
			char byte;
			while(!fim && codchar!='\0' && !inFile.eof()) {
				inFile.read(&byte,sizeof(char));
				for(unsigned int i=0; i<8; i++) {
					if((byte&MASK)==0x00) // caso 0, desce p filho esquerdo
						actualNode=actualNode->getLeft();
					else
						if((byte&MASK)==MASK) //caso 1, desce para filho direito
							actualNode=actualNode->getRight();

					if(actualNode->isLeaf()) { //se for uma folha, chegou-se a um caracter
						if((int)actualNode->getCaracter()==3) { //caracter ETX (end of text)
							fim=true; 							//termina transcricao
							break;
						}
						outFile << actualNode->getCaracter();
						actualNode=root;
					}
					byte=byte<<1;
				}
			}
			outFile.close();
		}
		else {
			cout << "Impossivel criar ficheiro de descodificacao!" << endl;
			return;
		}
		inFile.close();
	}
	else {
		cout << "Impossivel abrir ficheiro codificado!" << endl;
		return;
	}
	cout << "Ficheiro descomprimido!" << endl;
}
